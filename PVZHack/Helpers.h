#include <io.h>
#include <fcntl.h>
#include <iostream>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#define GameBase 0x140000000
#define GameSize 0x235D000
enum OffsetType{
	Sig, Hash
};

namespace Helpers
{


	static void* DetourFunc(BYTE *src, const BYTE *dst, const int len)
	{
		BYTE *jmp = (BYTE*)malloc(len + 5);

		DWORD dwback;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback);

		memcpy(jmp, src, len);
		jmp += len;

		jmp[0] = 0xE9;
		//relative address from trampoline to orig function + 5
		*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

		src[0] = 0xE9;
		*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

		VirtualProtect(src, len, dwback, &dwback);

		//address to trampoline
		return (jmp - len);
	}

	bool IsAlive(ClientPVZSoldierEntity* pSoldier)
	{
		if (!IsValidPtr(pSoldier))
			return false;

		ClientPVZSoldierHealthComponent* pHealth = pSoldier->m_ClientSoldierHealthComponent;
		if (!IsValidPtr(pHealth))
			return false;

		if (pHealth->m_Health < 0.00001f)
			return false;

		return true;
	}

	bool UpdateBones(ClientPVZSoldierEntity* pSoldier)
	{
		if (!IsValidPtr(pSoldier))
			return false;

		ClientSoldierAntAnimatableComponent* pAntComp = pSoldier->m_AntAnimatableComponent;
		if (!IsValidPtr(pAntComp))
			return false;

		GameAnimatable* pAnimatable = pAntComp->m_Handler;
		if (!IsValidPtr(pAnimatable))
			return false;

		pAnimatable->m_HadVisualUpdate = true;
		return true;
	}

	bool GetBone(ClientPVZSoldierEntity* pEnt, Vec3 *vOut, int BoneId)
	{
		if (!IsValidPtr(pEnt))
			return false;

		ClientRagdollComponent* pRag = pEnt->m_RagdollComponent;
		if (!IsValidPtr(pRag))
			return false;

		UpdatePoseResultData PoseResult = pRag->m_UpdatePoseResultData;
		if (PoseResult.m_ValidTransforms)
		{
			QuatTransform* pQuat = PoseResult.m_ActiveWorldTransforms;
			if (!IsValidPtr(pQuat))
				return false;

			Vec4 Temp = pQuat[BoneId].m_TransAndScale;

			vOut->x = Temp.x;
			vOut->y = Temp.y;
			vOut->z = Temp.z;
			return true;
		}
		else{
			return false;
		}
	}

	Screen* GetScreen()
	{
		DxRenderer* pDXRenderer = DxRenderer::GetInstance();
		if (!IsValidPtr(pDXRenderer))
			return nullptr;

		Screen* pScreen = pDXRenderer->m_pScreen;
		if (!IsValidPtr(pScreen))
			return nullptr;

		return pScreen;
	}
	
	RenderView* GetRenderView()
	{
		GameRenderer* pGameRenderer = GameRenderer::GetInstance();
		if (!IsValidPtr(pGameRenderer))
			return nullptr;

		RenderView* pRenderView = pGameRenderer->m_pRenderView;
		if (!IsValidPtr(pRenderView))
			return nullptr;

		return pRenderView;
	}


	bool WorldToScreen(const Vec3 in, Vec3& out)
	{
		out.x = 0;
		out.y = 0;

		RenderView* pRenderView = GetRenderView();
		if (!IsValidPtr(pRenderView))
			return false;

		D3DXMATRIX viewProjectionMatrix = pRenderView->m_viewProjectionMatrix;

		Screen* pScreen = GetScreen();
		if (!IsValidPtr(pScreen))
			return false;

		int iCenterY = pScreen->m_WindowHeight * .5;
		int iCenterX = pScreen->m_WindowWidth *.5;

		D3DXVECTOR3 Origin = D3DXVECTOR3(in.x, in.y, in.z);

		FLOAT w = viewProjectionMatrix.m[0][3] * Origin.x +
			viewProjectionMatrix.m[1][3] * Origin.y +
			viewProjectionMatrix.m[2][3] * Origin.z +
			viewProjectionMatrix.m[3][3];

		if (w < 0.0001f)
		{
			out.x = 0;
			out.y = 0;
			out.z = w;
			return false;
		}

		float x = viewProjectionMatrix.m[0][0] * Origin.x +
			viewProjectionMatrix.m[1][0] * Origin.y +
			viewProjectionMatrix.m[2][0] * Origin.z +
			viewProjectionMatrix.m[3][0];

		float y = viewProjectionMatrix.m[0][1] * Origin.x +
			viewProjectionMatrix.m[1][1] * Origin.y +
			viewProjectionMatrix.m[2][1] * Origin.z +
			viewProjectionMatrix.m[3][1];

		out.x = static_cast<int>(iCenterX + iCenterX * x / w);
		out.y = static_cast<int>(iCenterY - iCenterY * y / w);
		out.z = w;
		return true;
	}

	bool WorldToScreen(Vec3& vec)
	{
		RenderView* pRenderView = GetRenderView();
		if (!IsValidPtr(pRenderView))
			return false;

		D3DXMATRIX viewProjectionMatrix = pRenderView->m_viewProjectionMatrix;

		Screen* pScreen = GetScreen();
		if (!IsValidPtr(pScreen))
			return false;

		int iCenterY = pScreen->m_WindowHeight * .5;
		int iCenterX = pScreen->m_WindowWidth *.5;

		D3DXVECTOR3 Origin = D3DXVECTOR3(vec.x, vec.y, vec.z);

		FLOAT w = viewProjectionMatrix.m[0][3] * Origin.x +
			viewProjectionMatrix.m[1][3] * Origin.y +
			viewProjectionMatrix.m[2][3] * Origin.z +
			viewProjectionMatrix.m[3][3];

		if (w < 0.0001f)
		{
			vec.x = 0;
			vec.y = 0;
			vec.z = w;
			return false;
		}

		float x = viewProjectionMatrix.m[0][0] * Origin.x +
			viewProjectionMatrix.m[1][0] * Origin.y +
			viewProjectionMatrix.m[2][0] * Origin.z +
			viewProjectionMatrix.m[3][0];

		float y = viewProjectionMatrix.m[0][1] * Origin.x +
			viewProjectionMatrix.m[1][1] * Origin.y +
			viewProjectionMatrix.m[2][1] * Origin.z +
			viewProjectionMatrix.m[3][1];

		vec.x = static_cast<int>(iCenterX + iCenterX * x / w);
		vec.y = static_cast<int>(iCenterY - iCenterY * y / w);
		vec.z = w;
		return true;
	}

	void AimCorrection(Vec3 LocalPos, Vec3 EnemyPos, Vec3 MyVelocity, Vec3 EnemyVelocity, Vec3& InVec, float Distance, float Bulletspeed, float Gravity = 9.81f, Vec3 MyAccel = Vec3(0, 0, 0), Vec3 EnemyAccel = Vec3(0, 0, 0))
	{
		FLOAT m_time = Distance / fabs(Bulletspeed); //distance=rate*time
		FLOAT m_grav = fabs(Gravity);
		InVec = InVec + (EnemyVelocity * m_time) + (EnemyAccel*(m_time*m_time)*.5f);
		//*InVec    = *InVec - (MyVelocity * m_time) + (.5f*MyAccel*(m_time*m_time)) ;
		InVec.y += 0.5 * m_grav * m_time * m_time;
	}
	float VectorLength2D(Vec3& pV)
	{
		return	sqrtf(pV.x * pV.x + pV.z * pV.z);
	}
	float VectorLength3D(Vec3& pV)
	{
		return sqrtf(pV.x * pV.x + pV.y*pV.y + pV.z * pV.z);
	}
	bool IsInFOV(Vec3 forward, Vec3 EnemyPos, Vec3 LocalPos, float fov)
	{
		Vec3 DeltaDirection,forward_temp;
		forward_temp = forward;
		DeltaDirection = (EnemyPos - LocalPos);

		forward_temp.normalize();
		DeltaDirection.normalize();

		float angle = acos(forward.Dot(DeltaDirection));
		angle = D3DXToDegree(angle);

		if (angle > (fov / 2))
			return false;

		return true;
	}
	void RemoveDispersion(FiringDispersionData& dispData)
	{
		dispData.m_MaxAngle = 1.0f;
		dispData.m_MinAngle = 0.0f;
		dispData.m_IncreasePerShot = 0.0f;
	}
	bool TransformAABB(AxisAlignedBB aabb,AxisAlignedBB2& aabb_Screen,Vec3 Origin)
	{
		AxisAlignedBB2 aabb2;
		aabb2.m_Min = Vec3(aabb.m_Min.x, aabb.m_Min.y, aabb.m_Min.z);
		aabb2.m_Max = Vec3(aabb.m_Max.x, aabb.m_Max.y, aabb.m_Max.z);
		
		Vec3 min=aabb2.m_Min + Origin;
		Vec3 max = aabb2.m_Max + Origin;
		
		Vec3 crnr2 = Vec3(max.x, min.y, min.z);
		Vec3 crnr3 = Vec3(max.x, min.y, max.z);
		Vec3 crnr4 = Vec3(min.x, min.y, max.z);
		Vec3 crnr5 = Vec3(min.x, max.y, max.z);
		Vec3 crnr6 = Vec3(min.x, max.y, min.z);
		Vec3 crnr7 = Vec3(max.x, max.y, min.z);

		if (!WorldToScreen(min))
			return false;
		if (!WorldToScreen(max))
			return false;
		if (!WorldToScreen(crnr2))
			return false;
		if (!WorldToScreen(crnr3))
			return false;
		if (!WorldToScreen(crnr4))
			return false;
		if (!WorldToScreen(crnr5))
			return false;
		if (!WorldToScreen(crnr6))
			return false;
		if (!WorldToScreen(crnr7))
			return false;

		aabb_Screen.m_Min = min;
		aabb_Screen.m_Max = max;
		aabb_Screen.crnr2 = crnr2;
		aabb_Screen.crnr3 = crnr3;
		aabb_Screen.crnr4 = crnr4;
		aabb_Screen.crnr5 = crnr5;
		aabb_Screen.crnr6 = crnr6;
		aabb_Screen.crnr7 = crnr7;
	}

	void DrawAABB(AxisAlignedBB2 AABB,DebugRenderer* pRenderer,DWORD Color)
	{
		pRenderer->DrawLine(AABB.m_Min.x, AABB.m_Min.y, AABB.crnr2.x, AABB.crnr2.y, Color);
		pRenderer->DrawLine(AABB.m_Min.x, AABB.m_Min.y, AABB.crnr4.x, AABB.crnr4.y, Color);
		pRenderer->DrawLine(AABB.m_Min.x, AABB.m_Min.y, AABB.crnr6.x, AABB.crnr6.y, Color);

		//m_Max to 5,7,3
		pRenderer->DrawLine(AABB.m_Max.x, AABB.m_Max.y, AABB.crnr5.x, AABB.crnr5.y, Color);
		pRenderer->DrawLine(AABB.m_Max.x, AABB.m_Max.y, AABB.crnr7.x, AABB.crnr7.y, Color);
		pRenderer->DrawLine(AABB.m_Max.x, AABB.m_Max.y, AABB.crnr3.x, AABB.crnr3.y, Color);

		//2 to 7,3
		pRenderer->DrawLine(AABB.crnr2.x, AABB.crnr2.y, AABB.crnr3.x, AABB.crnr3.y, Color);
		pRenderer->DrawLine(AABB.crnr2.x, AABB.crnr2.y, AABB.crnr7.x, AABB.crnr7.y, Color);

		//4 to 5,3
		pRenderer->DrawLine(AABB.crnr4.x, AABB.crnr4.y, AABB.crnr5.x, AABB.crnr5.y, Color);
		pRenderer->DrawLine(AABB.crnr4.x, AABB.crnr4.y, AABB.crnr3.x, AABB.crnr3.y, Color);

		//6 to 5,7
		pRenderer->DrawLine(AABB.crnr6.x, AABB.crnr6.y, AABB.crnr5.x, AABB.crnr5.y, Color);
		pRenderer->DrawLine(AABB.crnr6.x, AABB.crnr6.y, AABB.crnr7.x, AABB.crnr7.y, Color);
	}

	class Signature
	{
	public:
		String m_Sig;
		Signature(String Name, String Sig, int Offset)
		{
			m_Name = Name;
			m_Sig = Sig;
			m_Offset = Offset;
		}
		static DWORD_PTR FindPattern(const char* pattern,bool SearchCodeOnly=false) //credits learn more
		{
			DWORD_PTR ModuleBase, ModuleSize;
			ModuleBase =(DWORD_PTR) GetModuleHandle(NULL);

			PIMAGE_DOS_HEADER DOS_Header = (PIMAGE_DOS_HEADER)(ModuleBase);
			PIMAGE_NT_HEADERS NT_Header = (PIMAGE_NT_HEADERS)(ModuleBase + DOS_Header->e_lfanew);

			if (SearchCodeOnly)
			{
				ModuleBase += NT_Header->OptionalHeader.BaseOfCode;
				ModuleSize = NT_Header->OptionalHeader.SizeOfCode;
			}else{
				//modulebase is already set by the getmodulehandleline
				ModuleSize = NT_Header->OptionalHeader.SizeOfImage;
			}
			

			//printf("Base:%I64X Size:%I64X Size2:%I64X \n", ModuleBase, ModuleSize);
			
			const char* pat = pattern;
			DWORD_PTR firstMatch = 0;
			for (DWORD_PTR pCur = ModuleBase; pCur < ModuleBase + ModuleSize; pCur++)
			{
				
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
				{
					if (!*pat) return firstMatch;
					if (!firstMatch) firstMatch = pCur;
					if (!pat[2]) return firstMatch;
					
					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else
						pat += 2;    //one ?
				}else{
					if (firstMatch != 0)
						pCur = firstMatch;
					pat = pattern;
					firstMatch = 0;
				}
			}
			return NULL;
		}

		DWORD_PTR ResolveRelativePtr(DWORD_PTR address, int offset)
		{
			if (address == NULL)
				return NULL;

			if (offset == 0)
				return address;
			address += offset;
			DWORD Val = *(DWORD_PTR*)address;
			return (address + Val + sizeof(DWORD));
		}
		String GetName()
		{
			return m_Name;
		}
		const String &GetSig()
		{
			return m_Sig;
		}
		int GetOffset()
		{
			return m_Offset;
		}
		void SetAddress(DWORD_PTR address)
		{
			m_Address = address;
		}
		DWORD_PTR GetAddress()
		{
			return m_Address;
		}
		OffsetType GetType()
		{
			return m_type;
		}
		void SetType(OffsetType type)
		{
			m_type = type;
		}
	private:
		String m_Name;
		int m_Offset;
		DWORD_PTR m_Address;
		OffsetType m_type;
	};

	class OffsetManager
	{
	public:
		
		Signature GetSigStruct(String Name)
		{
			for (auto& i : m_Signatures)
			{
				if (i.GetName() == Name)
				{
					return i;
				}
			}
		}
		void AddOffset(String Name, String Sig, int Offset,OffsetType type=OffsetType::Sig)
		{
			m_Signatures.emplace_back(Name, Sig, Offset);
		}
		void AddOffset(Signature Sig)
		{
			m_Signatures.push_back(Sig);
		}
		void FindSignatures()
		{
			for (int i = 0; i < m_Signatures.size(); i++)
			{
				int Attempts = 0;
				do 
				{
					
					String temp = m_Signatures[i].m_Sig;
					m_Signatures[i].SetAddress(
						m_Signatures[i].ResolveRelativePtr(
						m_Signatures[i].FindPattern(temp.c_str()),
						m_Signatures[i].GetOffset()));
				
					if (Attempts > 0)
					{
						Sleep(100);
						printf("Had trouble finding address %s \n", m_Signatures[i].GetName().c_str());
					}
					Attempts++;
				} while (m_Signatures[i].GetAddress() == NULL && Attempts <= 11);
			}
		}

		void PrintSignatures()
		{
			for (auto i : m_Signatures)
			{
				if (i.GetAddress() == NULL)
				{
					printf("%s: Unable To Find \n", i.GetName().c_str());
				}
				else{
					printf("%s: 0x%I64X \n", i.GetName().c_str(), i.GetAddress());
				}
			}
		}
	private:
		std::vector<Signature> m_Signatures;
	};
}