#include <windows.h>
#include "Tools.h"
#include <math.h>
#include <d3d11.h>
#include <D3DX10.h>
#include "Classes.h"
#include "DrawingClasses.h"
#include "VMTHook64.h"
#include "Helpers.h"
#include <MinHook.h>
#pragma comment(lib,"libMinHook.lib")
#include <GUIFrameWork.h>
#include "StringCrypt.h"
#include "Core.h"

bool EspEnabled = true;
bool NoRecoilEnabled = true;
bool AimbotEnabled = true;
bool ShouldSetupMenu = true;
bool ShowMenu = true;
bool EnableXPMod = true;

CVMTHookManager64* PresentHook = 0;
typedef HRESULT(__stdcall* tPresent)(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags);
tPresent oPresent; //our dx hook

//Tools::OffsetManager OffsetMngr;

HMODULE DllInst;
GUIManager *GUIMngr;
Core HackCore = Core();
XMFLOAT2 LastGoodMousePos;

void EjectDLL();

typedef BOOL(WINAPI* SETCURSORPOS)(int x, int y);
SETCURSORPOS origSetCursor = nullptr;
BOOL WINAPI hkSetCursor(int x,int y)
{
	if (ShowMenu)
	{
		if (GUIMngr->MouseInWindowBounds)
		{
			LastGoodMousePos = GUIMngr->m_MousePosition;
			return 1;
		}else{
			return origSetCursor(LastGoodMousePos.x, LastGoodMousePos.y);
		}
	}else{
		return origSetCursor(x, y);
	}
}
void HookSetCursor()
{
	if (MH_Initialize() == MH_OK)
	{
		if (MH_CreateHook(&SetCursorPos, &hkSetCursor, (void**)&origSetCursor) == MH_OK)
		{
			if (MH_EnableHook(&SetCursorPos) == MH_OK)
			{
				std::cout << "Hook Success \n";
			}else{
				std::cout << "Failed to Enable hook \n";
			}
		}else{
			std::cout << "Failed to Hook \n";
		}
	}else{
		std::cout << "Failed to initialize hook \n";
	}
}
void SetupMenu()
{
	DebugRenderer* pDebugRenderer = DebugRenderer::GetInstance();

	std::cout << "Got debuginst \n";
	DrawingAbstractor* pAbstractor = new DrawingAbstractor(pDebugRenderer);
	GUIMngr = new GUIManager(pAbstractor);

	Panel* pPanel = new Panel("Universal Cheats", "Univ Panel", XMFLOAT2(600.0f, 300.0f), XMFLOAT2(230.0f, 180.0f));

	pPanel->AddElement(
		new Label("ON", "Aimbot Label", XMFLOAT2(130.0f, 30.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel->AddElement(
		new Button("Toggle Aimbot", "Aimbot Btn", XMFLOAT2(10.0f, 30), XMFLOAT2(110.0f, 20.0f),
		[&]()->void
		{
			AimbotEnabled = !AimbotEnabled;		
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("Univ Panel");
			if (pTempPanel != nullptr)
			{
				Label* pLabel = pTempPanel->GetElement<Label>("Aimbot Label");
				if (pLabel != nullptr)
				{
					if (AimbotEnabled)
						pLabel->ChangeText("ON");
					else
						pLabel->ChangeText("OFF");
				}
			}
		}));

	pPanel->AddElement(
		new Label("ON", "Recoil Label", XMFLOAT2(130.0f, 55.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel->AddElement(
		new Button("Toggle Recoil", "Recoil Btn", XMFLOAT2(10.0f, 55.0f), XMFLOAT2(110.0f, 20.0f),
		[&]()->void
		{
			NoRecoilEnabled = !NoRecoilEnabled;
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("Univ Panel");
			if (pTempPanel != nullptr)
			{
				Label* pLabel = pTempPanel->GetElement<Label>("Recoil Label");
				if (pLabel != nullptr)
				{
					if (NoRecoilEnabled)
						pLabel->ChangeText("ON");
					else
						pLabel->ChangeText("OFF");
				}
			}
		}));

	pPanel->AddElement(
		new Label("Aimbot FOV", "FOV Label", XMFLOAT2(130.0f, 115.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel->AddElement(
		new Slider<int>("Fov", XMFLOAT2(20.0f, 115.0f), XMFLOAT2(50.0f, 15.0f), 0, 25, Colors::Black,
		[&]()->void
		{
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("Univ Panel");
			if (pTempPanel != nullptr)
			{
				auto pSlider = pTempPanel->GetElement<Slider<int>>("Fov");
				if (pSlider != nullptr)
					HackCore.m_FOV = pSlider->GetValue();
			}
		}));
	
	pPanel->AddElement(
		new Label("ON", "ESP Label", XMFLOAT2(130.0f, 80.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel->AddElement(
		new Button("Toggle ESP", "ESP Btn", XMFLOAT2(10.0f, 80.0f), XMFLOAT2(110.0f, 20.0f),
		[&]()->void
		{
			EspEnabled = !EspEnabled;
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("Univ Panel");
			if (pTempPanel != nullptr)
			{
				Label* pLabel=pTempPanel->GetElement<Label>("ESP Label");
				if (pLabel != nullptr)
				{
					if (EspEnabled)
						pLabel->ChangeText("ON");
					else
						pLabel->ChangeText("OFF");
				}
			}
		}));

	pPanel->AddElement(
		new Label("3D", "ESP Mode Label", XMFLOAT2(130.0f, 140.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel->AddElement(
		new Button("ESP Mode", "ESP Mode Btn", XMFLOAT2(10.0f, 140.0f), XMFLOAT2(110.0f,20.0f),
		[&]()->void
		{
			HackCore.Box3D = !HackCore.Box3D;
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("Univ Panel");
			if (pTempPanel != nullptr)
			{
				Label* pLabel = pTempPanel->GetElement<Label>("ESP Mode Label");
				if (pLabel != nullptr)
				{
					if (HackCore.Box3D)
						pLabel->ChangeText("3D");
					else
						pLabel->ChangeText("2D");
				}
			}
		}));

	Panel* pPanel2 = new Panel("Single Player Cheats", "SP Cheat Panel", XMFLOAT2(300.0f, 300.0f), XMFLOAT2(250.0f, 250.0f));

	pPanel2->AddElement(
		new Label("ON", "XP Label", XMFLOAT2(130.0f, 30.0f), XMFLOAT2(20.0f, 20.0f)));

	pPanel2->AddElement(
		new Button("Toggle XP", "XP Btn", XMFLOAT2(10.0f, 30.0f), XMFLOAT2(60.0f,20.0f),
		[&]()->void
		{
			EnableXPMod = !EnableXPMod;
			Panel* pTempPanel = GUIMngr->GetElement<Panel>("SP Cheat Panel");
			if (pTempPanel != nullptr)
			{
				Label* pLabel = pTempPanel->GetElement<Label>("XP Label");
				if (pLabel != nullptr)
				{
					if (EnableXPMod)
						pLabel->ChangeText("ON");
					else
						pLabel->ChangeText("OFF");
				}
			}
		}));

	pPanel2->AddElement(
		new Slider<int>("XP", XMFLOAT2(20.0f, 65.0f), XMFLOAT2(100.0f, 15.0f), 0, 10000, Colors::Black,
		[&]()->void
		{
		Panel* pTempPanel = GUIMngr->GetElement<Panel>("SP Cheat Panel");
		if (pTempPanel != nullptr)
		{
			auto pSlider = pTempPanel->GetElement<Slider<int>>("XP");
			if (pSlider != nullptr)
				HackCore.XP = (float)pSlider->GetValue();
		}
	}));

	GUIMngr->AddElement(pPanel);	
	GUIMngr->AddElement(pPanel2);
}
HRESULT hkPresent(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags)
{
	HackCore.CheckPlayerLife();
	if (EspEnabled)
		HackCore.RenderFrame();
	if (NoRecoilEnabled)
		HackCore.NoRecoil();
	
	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && AimbotEnabled)
		HackCore.Aimbot();
	
	if (ShouldSetupMenu)
	{
		SetupMenu();
		ShouldSetupMenu = false;
	}
	
	if (EnableXPMod)
		HackCore.XPMod();
	
	if (ShowMenu)
	{
		GUIMngr->DrawElements();
	}
	GUIMngr->UpdateMouse();
	GUIMngr->UpdateWindowInfo("PVZ Garden Warfare");
	return oPresent(thisptr, SyncInterval, Flags);
}
DWORD WINAPI InitThread(LPVOID lparam)
{
	HookSetCursor();
	//OffsetMngr.AddOffset("DXRenderer", "48 8B 0D ? ? ? ? 48 85 C9 74 0E E8 ? ? ? ? 48 8B A8 ? ? ? ? EB 19",0x141FDF650);
	DxRenderer* pDxRenderer = DxRenderer::GetInstance();
	while (!IsValidPtr(pDxRenderer))
	{
		DxRenderer* pDxRenderer = DxRenderer::GetInstance();
	}

	Screen* pScreen = pDxRenderer->m_pScreen;
	while (!IsValidPtr(pScreen))
	{
		Screen* pScreen = pDxRenderer->m_pScreen;
	}
		
	IDXGISwapChain* pSwap = pScreen->m_pSwapChain;
	while (!IsValidPtr(pSwap))
	{
		pSwap = pScreen->m_pSwapChain;
	}

	PresentHook = new CVMTHookManager64((DWORD64**)pSwap);
	oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
	PresentHook->dwHookMethod((DWORD64)hkPresent, 8);

	Helpers::OffsetManager mngr;
	mngr.AddOffset("DXRenderer", "48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 85 C0 75 2D 48 8B 05 ? ? ? ? 48 85 C0 75 1A", 3);
	mngr.AddOffset("GameContext", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 89 44 24 ? 4C 8D B6 ? ? ? ? 49 8B 3E 48 8B AE ? ? ? ?", 3);
	mngr.AddOffset("GameRenderer", "48 8B 0D ? ? ? ? 48 85 C9 74 06 48 8B 01 FF 50 50", 3);
	mngr.AddOffset("Dedicated Server Settings", "48 8B 05 ? ? ? ? 48 85 C0 75 1A 48 8D 15 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B 58 20 48 85 DB 74 06 48 8B 5B 28 EB 28", 3);
	mngr.AddOffset("DebugRenderer", "48 8B 0D ? ? ? ? 48 85 C9 75 03 33 C0 C3 E9 ? ? ? ?", 0);
	mngr.AddOffset("DrawText", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F9 41 8B F0 8B EA 48 83 CB FF 48 FF C3", 0);
	mngr.AddOffset("DrawLine", "48 89 5C 24 ? 44 89 4C 24 ? 57 48 83 EC 20 48 8B DA BA ? ? ? ? 49 8B F8 44 8D 42 FF E8 ? ? ? ? 8B 0B 89 08 8B 4B 04 48 8B 5C 24 ?", 0);
	mngr.AddOffset("DrawLineRect", "48 89 5C 24 ? 48 89 74 24 ? 44 89 4C 24 ? 57 48 83 EC 50 0F 29 74 24 ? F3 0F 10 32 0F 29 7C 24 ? F3 0F 10 7A ? 48 8B DA 49 8B F8 BA ? ? ? ? 48 8B F1 44 0F 29 44 24 ? F3 45 0F 10 00 44 8D 42 FF E8 ? ? ? ?", 0);
	mngr.FindSignatures();
	mngr.PrintSignatures();

	while (1)
	{
		if (GetAsyncKeyState(VK_F8) & 0x8000)
			EjectDLL();

		if (GetAsyncKeyState(VK_F7) & 0x8000)
		{
			ShowMenu = !ShowMenu;
			Sleep(200);
		}

		Sleep(100);
	}
    return 1;
}
void EjectDLL()
{
	PresentHook->UnHook();
	MH_DisableHook(&SetCursorPos);
	MH_Uninitialize();
	Sleep(2000);
	TerminateThread(InitThread, 0);
	
	FreeConsole();
	FreeLibraryAndExitThread(DllInst, 0);
}
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwAttached, LPVOID lpvReserved)
{
	if (dwAttached == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		DllInst = hModule;
		Tools::CreateConsole();
		HANDLE thread=CreateThread(NULL, NULL, InitThread, NULL, NULL, NULL);
		CloseHandle(thread);
	}
	return 1;
}