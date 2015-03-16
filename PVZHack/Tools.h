#ifndef TOOLS_H
#define TOOLS_H
#include <vector>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <Psapi.h> // for module size stuff
#include <fcntl.h>
#include <stdio.h>
#include <io.h>

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getbool( x )    (getBits(x[0]) << 4 | getBits(x[1]))

enum colour
{
	DARKBLUE = 1,
	DARKGREEN,
	DARKTEAL,
	DARKRED,
	DARKPINK,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	TEAL,
	RED,
	PINK,
	YELLOW,
	WHITE
};

namespace Tools
{

	void GetModuleAddressAndSize(const char* dllName, DWORD_PTR* base, DWORD_PTR* size, HMODULE ModuleHandle = NULL) //zoomgod http://www.unknowncheats.me/forum/633534-post5.html
	{

		MODULEINFO module;

		ZeroMemory(&module, sizeof(module));

		*base = 0;
		*size = 0;

		if (!ModuleHandle)
		{
			ModuleHandle = GetModuleHandleA(dllName);
		}
		if (GetModuleInformation(GetCurrentProcess(), ModuleHandle, &module, sizeof(module)))
		{
			*base = (DWORD_PTR)module.lpBaseOfDll;
			*size = (DWORD_PTR)module.SizeOfImage;
		}
	}

	void SetConsoleColor(colour PreColor, colour PostColor, char* text)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PreColor);
		std::cout << text << "\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PostColor);
	}

	void CreateConsole()
	{
		int hConHandle = 0;
		HANDLE lStdHandle = 0;
		FILE *fp = 0;

		AllocConsole();

		lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stdout = *fp;

		setvbuf(stdout, NULL, _IONBF, 0);
	}

	int GetRand(int min, int max)
	{
		//we do srand((unsigned)time(0)) in main
		int range = max - min;
		int random = min + int(range*rand()) / (RAND_MAX + 1);
		return random;
	}

	void* DetourVTable(void **VTable, int Function, void *Detour)
	{
		if (!VTable)
			return NULL;

		if (!Detour)
			return NULL;

		void *ret = VTable[Function];

		DWORD old;
		VirtualProtect(&(VTable[Function]), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
		VTable[Function] = Detour;
		VirtualProtect(&(VTable[Function]), sizeof(void*), old, &old);

		return ret;
	}

	void tprintf(const char* format) // base function
	{
		std::cout << format;
	}

	template<typename T, typename... Targs>
	void tprintf(const char* format, T value, Targs... Fargs)
	{
		for (; *format != '\0'; format++) {
			if (*format == '%' && (*(format + 1) == 'V' || *(format + 1) == 'v')) {
				std::cout << value;
				tprintf(format + 2, Fargs...); // recursive call
				return;
			}
			std::cout << *format;
		}
	}

	class OffsetManager
	{
	public:
		struct  Signature
		{
			String m_Name;
			String m_Sig;
			DWORD_PTR m_Offset;
			Signature(String Name, String Sig, DWORD_PTR Offset)
			{
				m_Name = Name;
				m_Sig = Sig;
				m_Offset = Offset;
			}
		};
		DWORD_PTR GetOffset(String Name)
		{
			for (auto i : m_Signatures)
			{
				if (i.m_Name == Name)
				{
					return i.m_Offset;
				}
			}
		}
		Signature GetSigStruct(String Name)
		{
			for (auto& i : m_Signatures)
			{
				if (i.m_Name == Name)
				{
					return i;
				}
			}
		}
		void AddOffset(String Name, String Sig, DWORD_PTR Offset)
		{
			m_Signatures.emplace_back(Name, Sig, Offset);
		}
		void AddOffset(Signature Sig)
		{
			m_Signatures.push_back(Sig);
		}
		DWORD_PTR FindPattern(DWORD_PTR rangeStart, DWORD_PTR rangeEnd, const char* pattern)//Learn_more
		{
			const char* pat = pattern;
			DWORD_PTR firstMatch = 0;
			for (DWORD_PTR pCur = rangeStart; pCur < rangeEnd; pCur++)
			{
				if (!*pat) return firstMatch;
				if (*(PBYTE)pat == '\?' || *(bool*)pCur == getbool(pat)) {
					if (!firstMatch) firstMatch = pCur;
					if (!pat[2]) return firstMatch;
					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
					else pat += 2;    //one ?
				}
				else {
					pat = pattern;
					firstMatch = 0;
				}
			}
			return NULL;
		}
	private:
		std::vector<Signature> m_Signatures;
	};
}
#define POINTERCHK( pointer ) ( pointer  && pointer !=0 && pointer!=nullptr  && HIWORD( pointer ) )

#pragma code_seg(push, ".text")
__declspec(allocate(".text"))
UCHAR return_bytes[4] = { 0x48, 0x8B, 0x01, 0xC3 };
#pragma code_seg()

typedef PVOID (*tPtrReadChk)(PVOID);
static const tPtrReadChk ChkPtrRead = (tPtrReadChk)&return_bytes;

#define InvalidPtrAccess ((PVOID)0x1338cafebabef00d)

#ifdef _AMD64_
#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)
#define _VALUE ULONG_PTR
#define _Allign 0x7
#else
#define _PTR_MAX_VALUE ((PVOID)0xFFF00000)
#define _VALUE ULONG
#define _Allign 0x3
#endif
__forceinline bool IsValidPtr(PVOID p)    { return (p >= (PVOID)0x10000) && (p < _PTR_MAX_VALUE) && p != nullptr && ChkPtrRead(p) != InvalidPtrAccess; }
//#define IsValidPtr( pointer ) ( pointer  && pointer !=0 && pointer!=nullptr  && HIWORD( pointer ) )

LONG NTAPI EH(_EXCEPTION_POINTERS *ExceptionInfo)
{
	if (ExceptionInfo->ContextRecord->Rip != (ULONG_PTR)return_bytes) //don't go yet
		return EXCEPTION_CONTINUE_SEARCH;

	ExceptionInfo->ContextRecord->Rip += 3;
	ExceptionInfo->ContextRecord->Rax = (ULONG_PTR)return_bytes; //we crashed so return

	return EXCEPTION_CONTINUE_EXECUTION;
}
#endif