#define ABGR(a,b,g,r) \
	((DWORD_PTR)((((a)& 0xff) << 24) | (((b)& 0xff) << 16) | (((g)& 0xff) << 8) | ((r)& 0xff)))

class Color32
{
public:
	union
	{
		struct
		{
			BYTE R;
			BYTE G;
			BYTE B;
			BYTE A;
		};
		DWORD dwColor;
	};

public:
	Color32(const DWORD _Color)
	{
		dwColor = _Color;
	}

	Color32(const BYTE Red, const BYTE Green, const BYTE Blue, const BYTE Alpha)
	{
		A = Alpha;
		R = Red;
		G = Green;
		B = Blue;
	}
	DWORD GetColor()
	{
		return dwColor;
	}
};
//String NullRenderers can get close to the renderfuncs
#define OFFSET_DEBUGRENDERER 0x1403A7100//0x141EABCD8// 0x1403A6CB0//0x1403A6FF0//0x14039EFA0 //48 8B 0D ? ? ? ? 48 85 C9 75 03 33 C0 C3 E9 ? ? ? ? 
#define OFFSET_DRAWTEXT     0x1403A8410//0x1403A8150//0x1403A83A0//0x1403A04E0 // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F9 41 8B F0 8B EA 48 83 CB FF 48 FF C3
#define OFFSET_DRAWLINE    0x1403A8140 //0x1403A7E80//0x1403A80D0//0x1403A0210 //48 89 5C 24 ? 44 89 4C 24 ? 57 48 83 EC 20 48 8B DA BA ? ? ? ? 49 8B F8 44 8D 42 FF E8 ? ? ? ? 8B 0B 89 08 8B 4B 04 48 8B 5C 24 ?
#define OFFSET_DRAWLINERECT 0x1403A81B0//0x1403A7EF0//0x1403A8140//0x1403A0280 //48 89 5C 24 ? 48 89 74 24 ? 44 89 4C 24 ? 57 48 83 EC 50 0F 29 74 24 ? F3 0F 10 32 0F 29 7C 24 ? F3 0F 10 7A ? 48 8B DA 49 8B F8 BA ? ? ? ? 48 8B F1 44 0F 29 44 24 ? F3 45 0F 10 00 44 8D 42 FF E8 ? ? ? ?
//No Filled Rect in the game
class DebugRenderer
{
public:
	static DebugRenderer* GetInstance(void)
	{
		typedef DebugRenderer *(__stdcall* tDebugRenderManagerGetThreadContext)(void);
		tDebugRenderManagerGetThreadContext pDebugRenderManagerGetThreadContext = (tDebugRenderManagerGetThreadContext)OFFSET_DEBUGRENDERER;
		return pDebugRenderManagerGetThreadContext();
	}

	void RenderText(float fx, float fy, DWORD dwColor,const char* szText, ...)
	{
		int a = (dwColor >> 24) & 0xff;
		int r = (dwColor >> 16) & 0xff;
		int g = (dwColor >> 8) & 0xff;
		int b = (dwColor)& 0xff;

		dwColor = ABGR(a, b, g, r);

		va_list va_alist;
		char szBuffer[9000];

		va_start(va_alist, szText);
		_vsnprintf_s(szBuffer, sizeof(szBuffer), szText, va_alist);
		va_end(va_alist);

		this->DrawText(fx, fy, dwColor, szBuffer, 1.0f);
	}

	void DrawText(int x, int y, Color32 color, char* text, float scale)
	{
		typedef void(__thiscall *tDrawText)(DebugRenderer*, int, int, char*, Color32, float);
		tDrawText pDrawText = (tDrawText)OFFSET_DRAWTEXT;
		pDrawText(this, x, y, text, color, scale);
	}
	void DrawLineRect(int x, int y, int width, int height, Color32 color)
	{
		eastl::Tuple2< float > tupMin = eastl::Tuple2< float >(x, y);
		eastl::Tuple2< float > tupMax = eastl::Tuple2< float >(x + width, y + height);

		typedef void(__thiscall* tDrawRectangle)(DebugRenderer*, eastl::Tuple2< float >*, eastl::Tuple2< float >*, Color32);
		tDrawRectangle oDrawRectangle = (tDrawRectangle)OFFSET_DRAWLINERECT;

		oDrawRectangle(this, &tupMin, &tupMax, color);
	}
	void DrawLine(int x1, int y1, int x2, int y2, Color32 color)
	{
		eastl::Tuple2< float > tupFrom = eastl::Tuple2< float >(x1, y1);
		eastl::Tuple2< float > tupTo = eastl::Tuple2< float >(x2, y2);

		typedef void(__thiscall* tDrawLine)(DebugRenderer*, eastl::Tuple2< float >*, eastl::Tuple2< float >*, Color32);
		tDrawLine oDrawLine = (tDrawLine)OFFSET_DRAWLINE;

		oDrawLine(this, &tupFrom, &tupTo, color);
	}
};
