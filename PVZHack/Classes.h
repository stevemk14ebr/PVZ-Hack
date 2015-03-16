#include <atlstr.h>
namespace eastl
{
	template <class T> class Tuple2
	{
	public:
		Tuple2(T e1, T e2) : _e1(e1), _e2(e2)
		{
		}

	public:
		T _e1;
		T _e2;
	};
}

class Vec4
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float data[4];
	};
	void print(char* pthis)
	{
		printf("%s Vec4 at 0x%.8X: (%5.1f|%5.1f|%5.1f)\n",pthis,this,x,y,z);
	}
	float len(void)
	{
		return sqrt(x*x + y*y + z*z);
	}
	void normalize(void)
	{
		float _l = len();
		this->x /= _l;
		this->y /= _l;
		this->z /= _l;
	}
	void initialize(void)
	{

		this->x /= 1;
		this->y /= 1;
		this->z = 1;
	}
	Vec4 operator * (float const &other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
		return *this;
	}
	Vec4 operator + (Vec4 const &other)
	{
		Vec4 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		v.z = this->z + other.z;
		return v;
	}
	
	Vec4 operator - (Vec4 const &other)
	{
		Vec4 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		v.z = this->z - other.z;
		return v;
	}
	Vec4 operator += (Vec4 const &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}
	//new from me 
	Vec4 operator -= (Vec4 const &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}
	bool operator ==(Vec4 const &other)
	{
		if (this->x == other.x)
		{
			if (this->y == other.y)
			{
				if (this->z == other.z)
				{
					return true;
				}
			}
		}
		return false;
	}
	//new from me Calculate Dotproduct
	float Dot(Vec4 Vec)
	{
		return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
	}

	// new from me get VecLength
	float VectorLength()
	{
		return sqrt(((this->x)*(this->x)) + ((this->y)*(this->y)) + ((this->z)*(this->z)));
	}
	float VectorLength2()
	{
		return sqrt(((this->x)*(this->x)) + ((this->z)*(this->z)));
	}
	//new from me get distance to vec
	float DistanceToVector(Vec4 const &other)
	{
		Vec4 Distance;
		Distance.x = other.x - this->x;
		Distance.y = other.y - this->y;
		Distance.z = other.z - this->z;
		return sqrt((Distance.x * Distance.x) + (Distance.y * Distance.y) + (Distance.z * Distance.z));
	}

	//new from me calc Veccrossize
	Vec4 VectorCrossSize(const Vec4 *pV1, const Vec4 *pV2)
	{
		this->x = pV1->y * pV2->z - pV1->z * pV2->y;
		this->y = pV1->z * pV2->x - pV1->x * pV2->z;
		this->z = pV1->x * pV2->y - pV1->y * pV2->x;
		return *this;
	}
};
class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			
		};
		float data[3];
	};
	Vec3(float tx, float ty, float tz)
	{
		x = tx;
		y = ty;
		z = tz;
	}
	Vec3(float tx, float ty)
	{
		x = tx;
		y = ty;
		z = 0.0f;
	}
	Vec3()
	{
		z=y=x= 0;
	}
	void print(int num=0)
	{
		printf("%i Vec3 (%5.1f|%5.1f|%5.1f)\n",num, x, y, z);
	}
	float len(void)
	{
		return sqrt(x*x + y*y + z*z);
	}
	void normalize(void)
	{
		float _l = len();
		this->x /= _l;
		this->y /= _l;
		this->z /= _l;
	}
	void initialize(void)
	{

		this->x /= 1;
		this->y /= 1;
		this->z = 1;
	}
	Vec3 operator * (float const &other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
		return *this;
	}
	Vec3 operator + (Vec3 const &other)
	{
		Vec3 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		v.z = this->z + other.z;
		return v;
	}
	Vec3 operator - (Vec3 const &other)
	{
		Vec3 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		v.z = this->z - other.z;
		return v;
	}
	Vec3 operator += (Vec3 const &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}
	//new from me 
	Vec3 operator -= (Vec3 const &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}
	bool operator ==(Vec3 const &other)
	{
		if (this->x == other.x)
		{
			if (this->y == other.y)
			{
				if (this->z == other.z)
				{
					return true;
				}
			}
		}
		return false;
	}
	//new from me Calculate Dotproduct
	float Dot(Vec3 Vec)
	{
		return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
	}

	// new from me get VecLength
	float VectorLength()
	{
		return sqrt(((this->x)*(this->x)) + ((this->y)*(this->y)) + ((this->z)*(this->z)));
	}
	float VectorLength2()
	{
		return sqrt(((this->x)*(this->x)) + ((this->z)*(this->z)));
	}
	//new from me get distance to vec
	float DistanceToVector(Vec3 const &other)
	{
		Vec3 Distance;
		Distance.x = other.x - this->x;
		Distance.y = other.y - this->y;
		Distance.z = other.z - this->z;
		return sqrt((Distance.x * Distance.x) + (Distance.y * Distance.y) + (Distance.z * Distance.z));
	}

	//new from me calc Veccrossize
	Vec3 VectorCrossSize(const Vec3 *pV1, const Vec3 *pV2)
	{
		this->x = pV1->y * pV2->z - pV1->z * pV2->y;
		this->y = pV1->z * pV2->x - pV1->x * pV2->z;
		this->z = pV1->x * pV2->y - pV1->y * pV2->x;
		return *this;
	}
};

class ClientSoldierBodyComponent;
class SoldierBodyComponentData;
class PeaShooter1;
class Peashooter2;
class PVZVisualUnlockasset;
class Class3;
class Class4;
class ResetAbilityBuffEffectData;
class MovementSpeedBuffEffectData;
class JumpHeightBuffEffectData;
class ClientCharacterEntity;
class Main;
class GameContext;
class PlayerManager;
class PlayerData;
class ClientPlayer;
class ClientPVZSoldierEntity;
class PVZSoldierEntityData;
class ClientPVZCharacterSpawnEntity;
class ClientPVZSoldierHealthComponent;
class ClientSoldierPhysicsComponent;
class CharacterPhysicsEntity;
class ClientSoldierAntAnimatableComponent;
class ClientSoldierCameraComponent;
class ClientRagdollComponent;
class ClientRagdollComponent;
class RagdollComponentData;
class UpdatePoseResultData;
class QuatTransform;
class GameAnimatable;
class ClientPVZSoldierWeaponsComponent;
class PVZSoldierWeaponsComponentData;
class Animatable;
class PVZWeapon;
class PVZWeaponFiringData;
class SoldierAimingSimulationData;
class SoldierAimAssistData;
class FiringFunctionData;
class GunSwayData;
class ClientPVZSoldierWeapon;
class PVZSoldierWeaponData;
class WeaponHandler;
class ClientSoldierAimingSimulation;
class AimAssist;
class MaterialDecl;
class LinearTransform;
class ServerSettings;
class GameSettings;

#define OFFSET_DXRENDERER	0x141FEB230//0x141FEA150//0x141FE7150//0x141FDE2D0 //48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 85 C0 75 2D 48 8B 05 ? ? ? ? 48 85 C0 75 1A 
#define OFFSET_GAMECONTEXT  0x141F000E0//0x141EFF000//0x141EFC000//0x141F2F1C0 //48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 89 44 24 ? 4C 8D B6 ? ? ? ? 49 8B 3E 48 8B AE ? ? ? ? 
#define OFFSET_GAMERENDERER   0x141F02218//0x141F01138//0x141EFE138//0x141F312F8 //48 8B 0D ? ? ? ? 48 85 C9 74 06 48 8B 01 FF 50 50 
#define OFFSET_BFSERVERSETTINGS 0x1421EFE10
#define OFFSET_BFDedicatedServerSettings 0x141C472E8//0x141C46268//0x141C43268 //0x141C76458 //48 8B 05 ? ? ? ? 48 85 C0 75 1A 48 8D 15 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B 58 20 48 85 DB 74 06 48 8B 5B 28 EB 28 
class RenderView
{
public:
	D3DXMATRIX unknown;
	D3DXMATRIX Transform;
	char unknown128[52]; //0x0080
	float fovY; //0x00B4  
	float defaultFovY; //0x00B8  
	float nearPlane; //0x00BC  
	float farPlane; //0x00C0  
	float aspect; //0x00C4  
	float orthoWidth; //0x00C8  
	float orthoHeight; //0x00CC  
	char unknown208[384]; //0x00D0
	float m_fovX; //0x0250  
	float m_depthToWidthRatio; //0x0254  
	float m_fovScale; //0x0258  
	float m_fovScaleSqr; //0x025C  
	D3DXMATRIX m_viewMatrix; //0x0260 
	D3DXMATRIX m_viewMatrixTranspose; //0x02A0
	D3DXMATRIX m_viewMatrixInverse; //0x02E0 
	D3DXMATRIX m_projectionMatrix; //0x0320 
	D3DXMATRIX m_viewMatrixAtOrigin; //0x0360
	D3DXMATRIX m_projectionMatrixTranspose; //0x03A0 
	D3DXMATRIX m_projectionMatrixInverse; //0x03E0 

	//char _0x0000[928];//992 
	D3DXMATRIX m_viewProjectionMatrix;//420 
	D3DXMATRIX m_ViewProjTranspose; //0x0460 
	D3DXMATRIX m_ViewProjInverse; //0x04A0 
	D3DXMATRIX m_UnknMatrix; //0x04E0   
	D3DXMATRIX m_Transform2; //0x0520  <-Appears to be copy of m_Transform
	D3DXMATRIX m_UnknMatrix2; //0x0560 

	void updateMatrix()
	{
		typedef void(__thiscall *tUpdateMat)(RenderView*, int);
		tUpdateMat UpdateMat = (tUpdateMat)0x14089BF70;
		UpdateMat(this, 0xf);
	}
};
class GameRenderer
{
public:
	char _0x0000[72];
	__int64 m_GameRenderSettings; //0x0048 GameRenderSettings
	char _0x0050[16];
	RenderView* m_pRenderView; //0x0060 
	char _0x0068[16];
	static GameRenderer* GetInstance()
	{
		return *(GameRenderer**)OFFSET_GAMERENDERER;
	}
};//Size=0x0078

class Screen
{
public:
	char _0x0000[80];
	__int32 m_Width; //0x0050 
	__int32 m_Height; //0x0054 
	__int32 m_WindowWidth; //0x0058 
	__int32 m_WindowHeight; //0x005C 
	char _0x0060[40];
	__int64 m_pTargetView; //0x0088 fb::DxRenderTargetView 
	char _0x0090[96];
	IDXGISwapChain* m_pSwapChain; //0x00F0 
	char _0x00F8[544];
	__int64 m_pShaderSystemSettings; //0x0318
};//Size=0x004

class DxRenderer
{
public:
	char _0x0000[56];
	Screen* m_pScreen;     //0x0038 
	char _0x0040[64];
	__int64 m_pDxDisplaySettings;  //0x0080 fb::DxDisplaySettings
	char _0x0088[120];
	ID3D11Device* m_pDevice;   //0x0100
	ID3D11DeviceContext* m_pContext; //0x0108
	static DxRenderer* GetInstance()
	{
		return *(DxRenderer**)OFFSET_DXRENDERER;
	}
};

class GamePlatform
{
public:
	__int32 m_Platform; //0x0000 
	char _0x0004[4];
};//Size=0x0008

class SettingsManager
{
public:
	char _0x0000[8];
	GameSettings* m_GameSettings; //0x0008 GameSettings
	char _0x0010[120];
	ServerSettings* m_ServerSettings; //0x0088 ServerSettings

};//Size=0x0090

class LogFileCollisionMode
{
public:
	__int32 m_Mode; //0x0000 

};//Size=0x0004

class VersionData
{
public:
	char _0x0000[24];
	char* m_Disclaimer; //0x0018 
	__int64 m_Version; //0x0020 
	char* m_DateTime; //0x0028 
	char* m_BranchID; //0x0030 
	char* m_GameName; //0x0038 
};//Size=0x0040

class WorldPartInclusion
{
public:
	char _0x0000[64];

};//Size=0x0040

class PVZDifficultyData
{
public:
	char _0x0000[8];

};//Size=0x0008

class DifficultyDataArray
{
public:
	PVZDifficultyData m_DifficultyArray[8]; //0x0000 PVZDifficultyData

};//Size=0x0040

class DifficultyDatas
{
public:
	char _0x0000[24];
	DifficultyDataArray* m_Difficulties; //0x0018 
};//Size=0x0020

class SystemSettings
{
public:
	char _0x0000[16];
	char* m_Name; //0x0010 
	GamePlatform m_GamePlatform; //0x0018 

};//Size=0x0020

class GameSettings : public SystemSettings
{
public:
	__int32 m_MaxPlayerCount; //0x0020 
	__int32 m_MaxSpectatorCount; //0x0024 
	__int32 m_MinPlayerCountElimination; //0x0028 
	LogFileCollisionMode m_LogFileCollisionMode; //0x002C 
	__int64 m_LogFileRotationHistoryLength; //0x0030 
	char* m_Level; //0x0038 
	char* m_StartPoint; //0x0040 
	char _0x0048[8];
	char* m_ActiveGameModeViewDefinition; //0x0050 
	char* m_GameModeViewDefinitions; //0x0058 
	__int32 m_DefaultTeamID; //0x0060 
	__int32 m_PS3ContentRatingAge; //0x0064 
	__int64 m_LogHistory; //0x0068 
	VersionData* m_Version; //0x0070 VersionData
	__int64 m_LayerInclusionTable; //0x0078 WorldPartInclusion
	char* m_DefaultLayerInclusionTable; //0x0080 
	float m_TimeBeforeSpawnIsAllowed; //0x0088 
	float m_LevelWarmUpTime; //0x008C 
	float m_TimeToWaitForQuitTaskCompletion; //0x0090 
	char _0x0094[4];
	PlayerData* m_PlayerData; //0x0098 PlayerData
	DifficultyDatas* m_DifficultySettings; //0x00A0 DifficultyDatas
	__int32 m_DifficultyIndex; //0x00A8 
	__int32 m_CurrentSKU; //0x00AC 
	BYTE N0104C914; //0x00B0 
	char N0114EFB3[7]; //0x00B1 
	BYTE m_LogFileEnabled; //0x00B8 
	BYTE m_ResourceRefreshAlwaysAllowed; //0x00B9 
	BYTE m_SpawnMaxLocalPlayerOnStartup; //0x00BA 
	BYTE m_UseSpeedBasedDetailedCollision; //0x00BB 
	BYTE m_UseSingleWeaponSelector; //0x00BC 
	BYTE m_AutoAimEnabled; //0x00BD 
	BYTE m_HasUnlimitedAmmo; //0x00BE 
	BYTE m_HasUnlimitedMags; //0x00BF 
	BYTE m_RotateLogs; //0x00C0 
	BYTE m_AdjustVehicleCenterOfMass; //0x00C1 
	BYTE m_AimAssistEnabled; //0x00C2 
	BYTE m_AimAssistUsePolynomials; //0x00C3 
	BYTE m_ForceFreeStreaming; //0x00C4 
	BYTE m_ForceDisableFreeStreaming; //0x00C5 
	BYTE m_IsGodMode; //0x00C6 
	BYTE m_IsJesusMode; //0x00C7 
	BYTE m_ISJesusModeAI; //0x00C8 
	BYTE m_GameAdministrationEnabled; //0x00C9 
	BYTE m_AllowDestructionEnabled; //0x00CA 
	BYTE m_IsDemo; //0x00CB 

};//Size=0x00CC

class Main
{
public:
	char _0x0000[72];
	SettingsManager* m_SettingsManager; //0x0048 
	char _0x0050[64];

};//Size=0x0090

class GameContext
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char _0x0008[16];
	PlayerManager* m_PlayerManager; //0x0018 
	char _0x0020[32];
	static GameContext* GetInstance()
	{
		return *(GameContext**)OFFSET_GAMECONTEXT;
	}
};//Size=0x0040

class PlayerManager
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //

	PlayerData* m_PlayerData; //0x0008 PlayerData
	__int32 m_MaxPlayerCount; //0x0010 
	__int32 m_PlayerCountBit; //0x0014 
	__int32 m_PlayerIdBitCount; //0x0018 
	char _0x001C[684];
	ClientPlayer* m_LocalPlayer; //0x02C8 
	char _0x02D0[184];
	ClientPlayer** m_PlayerArray; //0x0388 PTR to PTR of ClientPlayerType

	ClientPlayer* At(unsigned int id)
	{
		if (!IsValidPtr(this))
			return nullptr;

		if (id < this->m_MaxPlayerCount)
			return this->m_PlayerArray[id];

		return nullptr;
	}
};//Size=0x0390

class PlayerData
{
public:
	char _0x0000[24];
	__int64 m_pPlayerViewData; //0x0018 PlayerViewData
	__int64 m_pEntryInputActionMapsData; //0x0020 EntryInputActionMapsData
	__int64 m_pInputActionMappingsData; //0x0028 InputActionMappingsData

};//Size=0x0030

class ClientPlayer
{
public:
	virtual ~ClientPlayer(); //
	virtual ClientCharacterEntity* GetCharacterEntity(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //

	PlayerData* m_PlayerData; //0x0008 PlayerData
	char _0x0010[8];
	char* m_Name; //0x0018 
	char _0x0020[536];
	__int64 m_pPVZSoldierCustimizationAsset; //0x0238 PVZSoldierCustomizationAsset
	char _0x0240[2684];
	__int32 m_TeamID; //0x0CBC 
	char _0x0CC0[256];
	ClientPVZSoldierEntity* m_ClientSoldierEntity; //0x0DC0 ClientPVZSoldierEntity

};//Size=0x0DC8

class AxisAlignedBB
{
public:
	Vec4 m_Min; //0x0000 
	Vec4 m_Max; //0x0010 
};//Size=0x0020

class CharacterPhysicsEntityCollisionShapes
{
public:
	char _0x0000[32];
	AxisAlignedBB m_aabbs[3]; //0x0020 
};//Size=0x0080

class AxisAlignedBB2
{
public:
	Vec3 m_Min; //0x0000 
	Vec3 m_Max; //0x0010 
	Vec3 crnr2;
	Vec3 crnr3;
	Vec3 crnr4;
	Vec3 crnr5;
	Vec3 crnr6;
	Vec3 crnr7;

	/*
	  .5------8
	.' |    . '|
	6---+--7'  |
	|   |  |   |
	|  ,4--+---3
	|.'    | .'
	1------2'

	1 = min
	8 = max
	*/
};//Size=0x0020

class CharacterPhysicsEntity
{
public:
	char _0x0000[24];
	ClientPVZSoldierEntity* m_Owner; //0x0018 ClientPVZSoldierEntity
	char _0x0020[144];
	CharacterPhysicsEntityCollisionShapes* m_CollisionShapes; //0x00B0 
	char _0x00B8[48];
	__int64 m_CharacterPhysicsData; //0x00E8 CharacterPhysicsData
	char _0x00F0[24];
};//Size=0x0108

class ClientSoldierPrediction
{
public:
	char _0x0000[8];
	CharacterPhysicsEntity* m_CharacterPhysicsEntity; //0x0008 CharacterPhysicsEntity
	char _0x0010[32];
	Vec3 m_Position; //0x0030 
	char _0x003C[20];
	Vec3 m_Velocity; //0x0050 
};//Size=0x005C

class ClientPVZSoldierEntity
{
public:
	virtual __int64 GetType();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void GetTransform(D3DXMATRIX* mTransform);

	char _0x0008[40];
	PVZSoldierEntityData* m_SoldierEntityData; //0x0030 PVZSoldierEntityData
	char _0x0038[256];
	ClientPVZCharacterSpawnEntity* m_ClientCharacterSpawnEntity; //0x0138 ClientPVZCharacterSpawnEntity
	char _0x0140[8];
	ClientPVZSoldierHealthComponent* m_ClientSoldierHealthComponent; //0x0148 ClientPVZSoldierHealthComponent
	ClientSoldierPhysicsComponent* m_ClientSoldierPhysicsComponent; //0x0150 ClientSoldierPhysicsComponent
	char _0x0158[104];
	CharacterPhysicsEntity* m_CharacterPhysicsEntity; //0x01C0 CharacterPhysicsEntity
	char _0x01C8[40];
	ClientSoldierAntAnimatableComponent* m_AntAnimatableComponent; //0x01F0 ClientSoldierAntAnimatableComponent
	ClientSoldierCameraComponent* m_CameraComponent; //0x01F8 ClientSoldierCameraComponent
	char _0x0200[712];
	ClientRagdollComponent* m_RagdollComponent; //0x04C8 ClientRagdollComponent
	char _0x04D0[24];
	ClientSoldierPrediction* m_PredictedController; //0x04E8 
	char _0x04F0[192];
	ClientPVZSoldierWeaponsComponent* m_ClientSoldierWeaponsComp; //0x05B0 ClientPVZSoldierWeaponsComponent
	ClientSoldierBodyComponent* m_BodyComponent; //0x05B8 ClientSoldierBodyComponent
	char _0x05C0[41];
	BYTE m_Occluded; //0x05E9 
	char _0x05EA[486];
	char* m_EntityName; //0x07D0 

	/*
	ClientSoldierPrediction* m_PredictedController; //0x04E8
	char _0x04F0[92];
	BYTE m_RenderFlags; //0x054C
	char _0x054D[99];
	ClientPVZSoldierWeaponsComponent* m_ClientSoldierWeaponsComp; //0x05B0
	*/

	bool Visible()
	{
		return !m_Occluded;
	}
};//Size=0x07D8

class PVZSoldierEntityData
{
public:
	char aSoldierEntityData[384]; //+0x00 Inherited
	Vec4 m_TargetHighlightColor; //+0x180
	float m_DynamicSpeedMultiplier; //+0x190
	float m_WeaponShootBoneVerticalOffset; //+0x194
	CString m_Identifier; //+0x198
	__int64 m_DeserterBuff; //+0x1A0
	bool m_TeleportImmortal; //+0x1A8
};

class ClientPVZCharacterSpawnEntity
{
public:
	char _0x0000[64];

};//Size=0x0040

class ClientPVZSoldierHealthComponent
{
public:
	char _0x0000[16];
	__int64* m_data; //0x0010 PVZSoldierHealthComponentData
	char _0x0018[8];
	float m_Health; //0x0020 
	float m_MaxHealth; //0x0024 
	char _0x0028[16];
	float m_Health2; //0x0038 
	char _0x003C[64];

};//Size=0x007C

class ClientSoldierPhysicsComponent
{
public:
	char _0x0000[64];

};//Size=0x0040

class ClientSoldierAntAnimatableComponent
{
public:
	char _0x0000[104];
	GameAnimatable* m_Handler; //0x0068 
};//Size=0x0070

class ClientSoldierCameraComponent
{
public:
	char _0x0000[1232];
	Vec3 m_Velocity; //0x04D0 
	char _0x04DC[20];
	Vec3 m_Position; //0x04F0 
	char _0x04FC[4];
};//Size=0x0500

class UpdatePoseResultData
{
public:
	QuatTransform* m_LocalTransform; //0x0000 
	QuatTransform* m_WorldTransform; //0x0008 
	QuatTransform* N051451FC; //0x0010 
	QuatTransform* N051451FD; //0x0018 
	QuatTransform* N051451FE; //0x0020 
	QuatTransform* m_ActiveWorldTransforms; //0x0028 
	QuatTransform* m_ActiveLocalTransforms; //0x0030 
	__int32 m_Slot; //0x0038 
	__int32 m_ReaderIndex; //0x003C 
	BYTE m_ValidTransforms; //0x0040 
	BYTE m_PoseUpdateEnabled; //0x0041 
	BYTE m_PoseNeeded; //0x0042 
};//Size=0x0043

class ClientRagdollComponent
{
public:
	char _0x0000[16];
	RagdollComponentData* m_RagdollCompData; //0x0010 RagdollComponentData
	char _0x0018[112];
	UpdatePoseResultData m_UpdatePoseResultData; //0x0088 

};//Size=0x00CB

class AntRef
{
public:
	class Guid
	{
	public:
		char pad[0x10];
	};
	Guid m_AssetGuid; //+0x0
	int m_ProjectId; //+0x10
};

class RagdollBinding
{
public:
	AntRef m_RagdollOnBack; //+0x0
	AntRef m_RagdollBlend; //+0x14
	AntRef m_RagdollBlendEarly; //+0x28
	AntRef m_RagdollForceBlendDisabled; //+0x3C
	AntRef m_RagdollActiveTime; //+0x50
	AntRef m_RagdollFullyBlendedIn; //+0x64
};

class SkeletonCollisionData
{
public:
	char aDataContainer[16]; //+0x00 Inherited
	__int64 m_SkeletonAsset;//+0x10 SkeletonAsset
	__int64 m_BoneCollisionData; //+0x18 SkeletonAsset
};

class MaterialDecl
{
public:
	unsigned int m_Packed; //+0x0
};

class RagdollComponentData
{
public:
	class RagdollAsset
	{
	public:
		char aAsset[24]; //+0x00 Inherited
		MaterialDecl* m_MaterialPair; //+0x18
		__int64 m_Resource; //+0x20 ResourceRef
		bool m_UseServerRagdoll; //+0x28
	};
	char aGameComponentData[112]; //+0x00 Inherited
	__int64 m_SkeletonAsset; //+0x70SkeletonAsset
	RagdollAsset* m_RagdollAsset; //+0x78
	SkeletonCollisionData* m_SkeletonCollisionData; //+0x80
	RagdollBinding m_Binding; //+0x88
	CString m_LeftLegBoneName; //+0x100
	CString m_RightLegBoneName; //+0x108
	CString m_ExtraLegBoneNames; //+0x110
	bool m_BoneMaterials; //+0x118
	bool m_BuoyantParts; //+0x120
	bool m_AllowClientTriggerOnBlend; //+0x128
};

class QuatTransform
{
public:
	Vec4 m_TransAndScale;         // 0x0000
	Vec4 m_Rotation;           // 0x0010
}; //Size = 0x0020

class GameAnimatable
{
public:
	char _0x0000[192];
	Animatable* m_Animatable; //0x00C0 Animatable
	char _0x00C8[8];
	__int32 m_InstanceID; //0x00D0 
	BYTE m_HadVisualUpdate; //0x00D4 This is 100% correct

};//Size=0x00D5

class ClientSoldierWeapon
{
public:
	char _0x0000[8];
	__int64 m_WeaponData; //0x0008 WeaponData
	char _0x0010[8];
	PVZWeaponFiringData* m_WepFiringData; //0x0018 PVZWeaponFiringData
	char _0x0020[32];
	D3DXMATRIX m_ShootSpace; //0x0040 
	D3DXMATRIX m_ShootSpaceIdentity; //0x0080 
};//Size=0x00C0

class ClientPVZSoldierWeaponsComponent
{
public:
	char _0x0000[16];
	PVZSoldierWeaponsComponentData* m_data; //0x0010 PVZSoldierWeaponsComponentData
	char _0x0018[1984];
	WeaponHandler* m_WepHandler; //0x07D8 
	char _0x07E0[1256];
	PVZWeapon* m_WeaponComponent; //0x0CC8 
};//Size=0x0CD0

class LinearTransform
{
public:
	Vec4 m_right; //+0x0
	Vec4 m_up; //+0x10
	Vec4 m_forward; //+0x20
	Vec4 m_trans; //+0x30
};

class AnimatedWeaponBinding
{
public:
	AntRef m_Deploy; //+0x0
	AntRef m_AltDeploy; //+0x14
	AntRef m_Undeploy; //+0x28
	AntRef m_QuickSwitch; //+0x3C
	AntRef m_Reload; //+0x50
	AntRef m_ReloadStage; //+0x64
	AntRef m_ReloadShotgun;//+0x78
	AntRef m_Fire; //+0x8C
	AntRef m_FireSingle; //+0xA0
	AntRef m_FireHoldAndRelease; //+0xB4
	AntRef m_FireSimple; //+0xC8
	AntRef m_FirstShotSpawned; //+0xDC
	AntRef m_BoltAction; //+0xF0
	AntRef m_PumpAction; //+0x104
	AntRef m_MeleeAttack; //+0x118
	AntRef m_QuickThrow; //+0x12C
	AntRef m_QuickThrowType;//+0x140
	AntRef m_AimBody; //+0x154
	AntRef m_AlwaysAimHead;//+0x168
	AntRef m_OneHanded; //+0x17C
	AntRef m_OneHandedAiming;//+0x190
	AntRef m_AimingEnabled; //+0x1A4
	AntRef m_LowerGun;//+0x1B8
	AntRef m_BreathControl;//+0x1CC
	AntRef m_RflType;//+0x1E0
	AntRef m_PstlType;//+0x1F4
	AntRef m_HgrType; //+0x208
	AntRef m_ATType; //+0x21C
	AntRef m_ShgType; //+0x230
	AntRef m_LMGType;//+0x244
	AntRef m_BagType;//+0x258
	AntRef m_SnpType;//+0x26C
	AntRef m_Zoom;//+0x280
	AntRef m_CantedZoom;//+0x294
	AntRef m_MagnifierSightToggle; //+0x2A8
	AntRef m_AimBodyWeight; //+0x2BC
	AntRef m_DisableZoomToggleWeight; //+0x2D0
	AntRef m_ZoomParameter; //+0x2E4
	AntRef m_ZoomScaleFactor; //+0x2F8
	AntRef m_Dispersion; //+0x30C
	AntRef m_AimTargetPosBody; //+0x320
	AntRef m_ZoomOutSpeed; //+0x334
	AntRef m_ZoomInSpeed; //+0x348
	AntRef m_UnDeploySpeed;//+0x35C
	AntRef m_DeploySpeed; //+0x370
	AntRef m_LightEnabled; //+0x384
	AntRef m_FireModeChanged; //+0x398
	AntRef m_AnimType; //+0x3AC
	AntRef m_GunDown; //+0x3C0
	AntRef m_AllowSwitchingToWeaponInWater; //+0x3D4
	AntRef m_NumberOfBulletsLeftInGun; //+0x3E8
	AntRef m_BulletsLeftInGun; //+0x3FC
	AntRef m_AbortVehicleDeploy; //+0x410
	AntRef m_CustomizeWeapon; //+0x424
	AntRef m_CustomizeWeaponSwitch; //+0x438
	AntRef m_WeaponActionESIG; //+0x44C
	AntRef m_IsSprinting; //+0x460
	AntRef m_PreparingToBash;//+0x474
	AntRef m_JustStartedSprinting;//+0x488
	AntRef m_KickbackMagnitudeFactor; //+0x49C
	AntRef m_KickbackSpeedFactor;//+0x4B0
	AntRef m_ZoomingTime;//+0x4C4
	AntRef m_TriggerZoomGunTwitch; //+0x4D8
	AntRef m_WeaponChooserSignal; //+0x4EC
	AntRef m_WeaponClassSignal; //+0x500
	AntRef m_WeaponCostumeChooserSignal; //+0x514
	AntRef m_OffsetX; //+0x528
	AntRef m_OffsetY;//+0x53C
	AntRef m_OffsetZ;//+0x550
	AntRef m_AIAllowFire;//+0x564
	AntRef m_AIAltFireFromAnt; //+0x578
};

class Animated1pOnlyWeaponBinding
{
public:
	AntRef m_UndeployFinished; //+0x0
	AntRef m_CameraFreeWeight;//+0x14
	AntRef m_Deploy1P; //+0x28
	AntRef m_HideWeapon1p; //+0x3C
};

class Animated3pOnlyWeaponBinding
{
public:
	AntRef m_Deploy3P; //+0x0
	AntRef m_HideWeapon3p; //+0x14
	AntRef m_WeaponAssembled3p; //+0x28
};

class PickupEntityAsset
{
public:
	char aDataContainerPolicyAsset[24]; //+0x00 Inherited
	__int64 m_Data; //+0x18 PickupEntityData
};

class SoldierWeaponsComponentData
{
public:
	char aGameComponentData[112]; //+0x00 Inherited
	LinearTransform m_AimDir; //+0x70
	int m_PrimaryWeaponId; //+0xB0
	SoldierAimingSimulationData* m_DefaultAimingController; //+0xB8
	AnimatedWeaponBinding m_AnimatedWeaponBinding; //+0xC0 AnimatedWeaponBinding
	Animated1pOnlyWeaponBinding m_Animated1pOnlyWeaponBinding; //+0x64C
	Animated3pOnlyWeaponBinding m_Animated3pOnlyWeaponBinding; //+0x69C
	__int64 m_WeaponSkeleton; //+0x6D8 SkeletonAsset
	float m_AmmoClipIncreaseMultiplier; //+0x6E0
	int m_GrenadeIncrease; //+0x6E4
	int m_UnderslungGrenadeIncrease; //+0x6E8
	float m_ExplosiveIncreaseMultiplier; //+0x6EC
	PickupEntityAsset* m_DropWeaponPickup; //+0x6F0
	bool m_UseExternalAimDir; //+0x6F8
	bool m_UnlimitedAmmo; //+0x6F9
	bool m_UnlimitedMags; //+0x6FA
	bool m_IsOwnedByAI; //+0x6FB
};

class PvZWeaponsBinding
{
public:
	AntRef m_WeaponFireStarted; //+0x0
	AntRef m_WeaponIsFiring; //+0x14
	AntRef m_SpawnedProjectile;//+0x28
	AntRef m_ReloadTimeMultiplier; //+0x3C
};

class PVZSoldierWeaponsComponentData
{
public:
	char aSoldierWeaponsComponentData[1792]; //+0x00 Inherited
	float m_OverheatingValue; //+0x700
	PvZWeaponsBinding m_PvZWeaponsAnimationBinding; //+0x704 might be a ptr
};

class Animatable
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //

	char _0x0008[112];

};//Size=0x0078

class PVZWeapon
{
public:
	char _0x0000[16];
	PVZWeaponFiringData* m_data; //0x0010 PVZWeaponFiringData
	char _0x0018[16];
	SoldierAimingSimulationData* m_AimingSimData; //0x0028 SoldierAimingSimulationData

};//Size=0x0030

class PVZWeaponFiringData
{
public:
	char _0x0000[16];
	FiringFunctionData* m_PrimaryFire; //0x0010 
	char _0x0018[24];
	GunSwayData* m_SwayData; //0x0030

};//Size=0x0038

class AimingPoseData
{
public:
	float m_MinimumPitch; //+0x0
	float m_MaximumPitch; //+0x4
	float m_TargetingFov; //+0x8
	float m_AimSteadiness; //+0xC
	float m_SpeedMultiplier; //+0x10
	float m_RecoilMultiplier; //+0x14
};

class SoldierAimingSimulationData
{
public:
	char aGameDataContainer[16]; //+0x00 Inherited
	__int64 m_ZoomLevels; //+0x10 GameDataContainer
	SoldierAimAssistData* m_AimAssist; //+0x18
	AimingPoseData m_StandPose; //+0x20
	AimingPoseData m_CrouchPose; //+0x38
	AimingPoseData m_PronePose; //+0x50
	float m_ZoomTransitionTime; //+0x68
	float m_ZoomTransitionTimeArray; //+0x70
	float m_FovDelayTime; //+0x78
	float m_FovTransitionTime; //+0x7C
	float m_AimingRange; //+0x80
	float m_LockAimToTargetSpeed; //+0x84
	float m_Modifiers; //+0x88
	bool m_ReturnToZoomAfterReload; //+0x90
};

class SoldierAimAssistData
{
public:
	char _0x0000[64];

};//Size=0x0040

class FiringDispersionData
{
public:
	float m_MinAngle; //0x0000 
	float m_MaxAngle; //0x0004 
	float m_IncreasePerShot; //0x0008 
	float m_DecreasePerSecond; //0x000C 
	float m_YawMultiplier; //0x0010 
	float m_PitchMultiplier; //0x0014 
}; //Size=0x0018

class WeaponDispersion
{
public:
	FiringDispersionData m_StandDispersion; //0x0000
	FiringDispersionData m_CrouchDispersion; //0x0018 
	FiringDispersionData m_ProneDispersion; //0x0030 
	float m_JumpDispersionAngle; //0x0048 
	float m_ProneTransitionDispersionAngle; //0x004C 
	float m_MoveDispersionAngle; //0x0050 
	float m_MoveZoomedDispersionAngle; //0x0054 
	float m_DecreasePerSecond; //0x0058 
	char _0x005C[4];
}; //Size=0x0060

class ProjectileEntityData
{
public:

	enum AntHitReactionWeaponType
	{
		AntHitReactionWeaponType_Pistol = 0,
		AntHitReactionWeaponType_SMG = 1,
		AntHitReactionWeaponType_AssaultRifle = 2,
		AntHitReactionWeaponType_LMG = 3,
		AntHitReactionWeaponType_Shotgun = 4,
		AntHitReactionWeaponType_SniperRifle = 5,
		AntHitReactionWeaponType_Explosion = 6,
		AntHitReactionWeaponType_Flashbang = 7,
		AntHitReactionWeaponType_Melee = 8
	};

	char _0x0000[128];
	__int64 m_pPhysicsData; //0x0080 fb::PhysicsEntityData* 
	char _0x0088[8];
	float m_InitialSpeed; //0x0090 
	float m_TimeToLive; //0x0094 
	__int32 m_MaxCount; //0x0098 
	float m_MaxCountCoolDownTime; //0x009C 
	float m_InitMeshHideTime; //0x00A0 
	float m_VisualConvergeDistance; //0x00A4 
	float m_VisualConvergenceDelay; //0x00A8 
	float m_VisualConvergenceDuration; //0x00AC 
	float m_ProxyVisualConvergenceDelay; //0x00B0 
	float m_ProxyVisualConvergenceDuration; //0x00B4 
	__int64 m_pExplosion; //0x00B8 fb::ExplosionEntityData* 
	__int64 m_pSuppressionData; //0x00C0 fb::WeaponSuppressionData* 
	char* m_pAmmunitionType; //0x00C8 
	__int32 m_MaterialPair; //0x00D0 fb::MaterialDecl 
	AntHitReactionWeaponType m_HitReactionWeaponType; //0x00D4pe 
	BYTE m_DetonateOnTimeout; //0x00D8 
	BYTE m_ServerProjectileDisabled; //0x00D9 
	char _0x00DA[6];
}; //Size=0x00E0

class MeshProjectileEntityData : public ProjectileEntityData
{
public:
	D3DXVECTOR4 m_InitialAngularVelocity; //0x00E0 
	__int64 m_pMesh; //0x00F0 fb::MeshAsset*
	__int64 m_pTrailEffect; //0x00F8 fb::EffectBlueprint* 
	float m_InstantAttachableTestDistance; //0x0100 
	float m_InstantAttachableVisualConvergenceDelay; //0x0104 
	float m_InstantAttachableVisualConvergenceDuration; //0x0108 
	float m_MaxAttachableInclination; //0x010C 
	float m_UnspawnAfterDetonationDelay; //0x0110 
	BYTE m_IsAttachable; //0x0114 
	BYTE m_InstantAttachableTestUnderReticule; //0x0115 
	BYTE m_ExtraDamping; //0x0116 
	char _0x0117[9];
}; //Size=0x0120

class BulletEntityData : public MeshProjectileEntityData
{
public:
	__int64 m_pFlyBySound; //0x0120 fb::SoundAsset* 
	__int64 m_pDudExplosion; //0x0128 fb::ExplosionEntityData* 
	float m_Gravity; //0x0130 
	float m_ImpactImpulse; //0x0134 
	float m_DetonationTimeVariation; //0x0138 
	float m_VehicleDetonationRadius; //0x013C 
	float m_VehicleDetonationActivationDelay; //0x0140 
	float m_FlyBySoundRadius; //0x0144 
	float m_FlyBySoundSpeed; //0x0148 
	float m_Stamina; //0x014C 
	float m_DistributeDamageOverTime; //0x0150 
	float m_StartDamage; //0x0154 
	float m_EndDamage; //0x0158 
	float m_DamageFalloffStartDistance; //0x015C 
	float m_DamageFalloffEndDistance; //0x0160 
	__int32 m_DamageType; //0x0164 
	float m_TimeToArmExplosion; //0x0168 
	float m_FirstFrameTravelDistance; //0x016C 
	float m_DespawnDelay; //0x0170 
	BYTE m_GroupDamage; //0x0174 
	BYTE m_HasVehicleDetonation; //0x0175 
	BYTE m_InstantHit; //0x0176 
	BYTE m_StopTrailEffectOnUnspawn; //0x0177 
}; //Size=0x0178

class ShotConfigData
{
public:
	D3DXVECTOR4 m_InitialPosition; //0x0000 
	D3DXVECTOR4 m_InitialDirection; //0x0010 
	D3DXVECTOR4 m_InitialSpeed; //0x0020 
	D3DXVECTOR2 m_InitialDirectionScaleByPitch; //0x0030 
	D3DXVECTOR2 m_InitialSpeedScaleByPitch; //0x0038 
	float m_RaycastDistance; //0x0040 
	float m_InheritWeaponSpeedAmount; //0x0044 
	__int64 m_pMuzzleExplosion; //0x0048 fb::ExplosionEntityData*
	BulletEntityData* m_pProjectileData; //0x0050 Originally fb::ProjectileEntityData
	BulletEntityData* m_pSecondaryProjectileData; //0x0058 
	__int64 m_pProjectile; //0x0060 fb::ProjectileBlueprint* 
	__int64 m_pSecondaryProjectile; //0x0068 fb::ProjectileBlueprint* 
	float m_SpawnDelay; //0x0070 
	__int32 m_NumberOfBulletsPerShell; //0x0074 
	__int32 m_NumberOfBulletsPerShot; //0x0078 
	__int32 m_NumberOfBulletsPerBurst; //0x007C 
	float m_WeaponHitDistanceMinimum; //0x0080 
	float m_WeaponRaycastVerticalOffset; //0x0084 
	float m_WeaponWallTestDist; //0x0088 
	BYTE m_ForceSpawnToCamera; //0x008C 
	BYTE m_SpawnVisualAtWeaponBone; //0x008D 
	BYTE m_ActiveForceSpawnToCamera; //0x008E 
	char _0x008F[1];
}; //Size=0x0090


class FireEffectData
{
public:
	D3DXVECTOR4 m_Offset; //0x0000 
	D3DXVECTOR4 m_Rotation; //0x0010 
	D3DXVECTOR4 m_ZoomOffset; //0x0020 
	D3DXVECTOR4 m_ZoomRotation; //0x0030 
	__int64 m_pEffect; //0x0040 fb::EffectBlueprint* 
	__int64 m_pChargingEffect; //0x0048 fb::EffectBlueprint*
	__int64 m_pChargeEffects; //0x0050 fb::EffectBlueprint*
	BYTE m_UseZoomOffset; //0x0058 
	BYTE m_UseZoomRotation; //0x0059 
	BYTE m_DisableDuringZoom; //0x005A 
	BYTE m_UpdateTransform; //0x005B 
	BYTE m_StopLoopingEffects; //0x005C 
	char _0x005D[3];
}; //Size=0x0060

class OverHeatData
{
public:
	FireEffectData m_OverHeatEffect; //0x0000 
	float m_HeatPerBullet; //0x0060 
	float m_HeatDropPerSecond; //0x0064 
	float m_OverHeatPenaltyTime; //0x0068 
	float m_OverHeatThreshold; //0x006C 
}; //Size=0x0070

class FireLogicData
{
public:

	enum ReloadLogic
	{
		rlWeaponSwitchCancelsUnfinishedReload = 0,
		rlReloadUnaffectedByWeaponSwitch = 1
	};

	enum ReloadType
	{
		rtSingleBullet = 0,
		rtMagazine = 1,
		rtMagazineWithPossibleShorterReload = 2
	};

	class HoldAndReleaseData
	{
	public:
		float m_MaxHoldTime; //0x0000 
		float m_MinPowerModifier; //0x0004 
		float m_MaxPowerModifier; //0x0008 
		float m_PowerIncreasePerSecond; //0x000C 
		float m_Delay; //0x0010 
		float m_KilledHoldingPowerModifier; //0x0014 
		float m_ChargeDelay; //0x0018 
		float m_ForceFireWhenKilledHolding; //0x001C 
	}; //Size=0x0020

	class BoltActionData
	{
	public:
		float m_BoltActionDelay; //0x0000 
		float m_BoltActionTime; //0x0004 
		BYTE m_HoldBoltActionUntilFireRelease; //0x0008 
		BYTE m_HoldBoltActionUntilZoomRelease; //0x0009 
		BYTE m_ForceBoltActionOnFireTrigger; //0x000A 
		BYTE m_UnZoomOnBoltAction; //0x000B 
		BYTE m_ReturnToZoomAfterBoltAction; //0x000C 
		char _0x000D[3];
	}; //Size=0x0010

	class RecoilData
	{
	public:
		float m_MaxRecoilAngleX; //0x0000 
		float m_MinRecoilAngleX; //0x0004 
		float m_MaxRecoilAngleY; //0x0008 
		float m_MinRecoilAngleY; //0x000C 
		float m_MaxRecoilAngleZ; //0x0010 
		float m_MinRecoilAngleZ; //0x0014 
		float m_MaxRecoilFov; //0x0018 
		float m_MinRecoilFov; //0x001C 
		float m_RecoilRecoveryTime; //0x0020 
		BYTE m_RecoilFollowsDispersion; //0x0024 
		char _0x0025[3];
	}; //Size=0x0028

	HoldAndReleaseData m_HoldAndRelease; //0x0000 
	BoltActionData BoltActionData; //0x0020 
	RecoilData RecoilData; //0x0030 
	__int32 m_FireInputAction; //0x0058 
	__int32 m_ReloadInputAction; //0x005C 
	__int32 m_CycleFireModeInputAction; //0x0060 
	float m_TriggerPullWeight; //0x0064 
	float m_RateOfFire; //0x0068 
	float m_RateOfFireForBurst; //0x006C 
	float m_ClientFireRateMultiplier; //0x0070 
	float m_ReloadDelay; //0x0074 
	float m_ReloadTime; //0x0078 
	float m_FirstReloadTimeOverride; //0x007C 
	__int64 m_ReloadTimerArray; //0x0080 
	float m_ReloadTimeBulletsLeft; //0x0088 
	float m_ReloadThreshold; //0x008C 
	float m_PreFireDelay; //0x0090 
	float m_AutomaticDelay; //0x0094 
	ReloadLogic m_ReloadLogic; //0x0098
	ReloadType m_ReloadType; //0x009C
	__int64 m_FireLogicType; //0x00A0 
	__int64 m_FireLogicTypeArray; //0x00A8 
	float m_AutomaticFirePrimingTime; //0x00B0 
	__int32 m_PrimingFireInputAction; //0x00B4 
	BYTE m_HoldOffReloadUntilFireRelease; //0x00B8 
	BYTE m_HoldOffReloadUntilZoomRelease; //0x00B9 
	BYTE m_ForceReloadActionOnFireTrigger; //0x00BA 
	BYTE m_AlwaysAutoReload; //0x00BB 
	char _0x00BC[4];
}; //Size=0x00C0

class AmmoConfigData
{
public:
	__int32 m_MagazineCapacity; //0x0000 
	__int32 m_NumberOfMagazines; //0x0004 
	unsigned int m_TraceFrequency; //0x0008
	unsigned int m_AmmoPickupMinAmount; //0x000C
	unsigned int m_AmmoPickupMaxAmount; //0x0010 
	float m_AutoReplenishDelay; //0x0014 
	float m_AmmoBagPickupDelayMultiplier; //0x0018 
	__int32 m_AmmoBagPickupAmount; //0x001C 
	BYTE m_AutoReplenishMagazine; //0x0020 
	BYTE m_ReplenishAtProjectileLimit; //0x0021 
	BYTE m_ReplenishOnDeactivate; //0x0022 
	char _0x0023[5];
}; //Size=0x002

class FiringFunctionData
{
public:
	char _0x0000[16];
	__int64 m_pDispersion; //0x0010 fb::GameDataContainer 
	WeaponDispersion m_WeaponDispersion; //0x0018 
	WeaponDispersion* m_pFireEffects1p; //0x0078 
	WeaponDispersion* m_pFireEffects3p; //0x0080 
	char _0x0088[8];
	ShotConfigData m_Shot; //0x0090 
	OverHeatData m_OverHeat; //0x0120 
	__int64 m_pSound; //0x0190 fb::SoundAsset* 
	__int64 m_pSound1p; //0x0198 fb::SoundAsset* 
	FireLogicData m_FireLogic; //0x01A0 
	AmmoConfigData m_Ammo; //0x0260 
	OverHeatData* m_pChargeShots; //0x0288 
	float m_ChargingEffectDelay; //0x0290 
	float m_SelfHealTimeWhenDeployed; //0x0294 
	__int32 m_ProjectileSpawnBone; //0x0298 
	__int32 m_ProjectileSpawnBoneAlt; //0x029 C
	__int32 m_ProjectileGraphicEffectsSpawnBone; //0x02A0 
	__int32 m_ProjectileGraphicEffectsSpawnBone_Alt; //0x02A4 
	BYTE m_UsePrimaryAmmo; //0x02A8 
	BYTE m_UnlimitedAmmoForAI; //0x02A9 
	char _0x02AA[6];
}; //Size=0x02B0

class GunSwayData
{
public:
	char _0x0000[864];
	float m_DeviateScaleFactorZoom; //0x0360 Set 0
	float m_GameplayDeviationFactorZoom; //0x0364 set 0
	float m_DeviationScaleFactorNoZoom; //0x0368 set 0
	float m_GameplayDeviationScaleFactorNoZoom; //0x036C set 0 
	float m_ShootingRecoilDecreaseScale; //0x0370 set 10,000
	float m_FirstShotMultiplier; //0x0374 set 0
	__int64 m_CameraRecoil; //0x0378 CameraRecoilData ignore
	char _0x0380[192];
};//Size=0x0440

class ClientPVZSoldierWeapon
{
public:
	char _0x0000[48];
	PVZSoldierWeaponData* m_WeaponData; //0x0030 PVZSoldierWeaponData
	char _0x0038[18776];
	ClientSoldierAimingSimulation* m_pAuthorativeAiming; //0x4990 
	char _0x4998[24];
	ClientSoldierWeapon* m_pClientWep; //0x49B0 ClientWeapon
};//Size=0x49B8

class PVZSoldierWeaponData
{
public:
	char _0x0000[64];

};//Size=0x0040

class WeaponHandler
{
public:
	char _0x0000[56];
	ClientPVZSoldierWeapon* m_SoldierWeapon; //0x0038 ClientPVZSoldierWeapon
	char _0x0040[24];
	ClientPVZSoldierEntity* m_Owner; //0x0058 ClientPVZSoldierEntity

};//Size=0x0060

class ClientSoldierAimingSimulation
{
public:
	char _0x0000[16];
	SoldierAimingSimulationData* m_data; //0x0010 SoldierAimingSimulationData
	char _0x0018[8];
	AimAssist* m_fpsAimer; //0x0020 
	float m_yaw; //0x0028 
	float m_pitch; //0x002C 
	float m_aimYawTimer; //0x0030 
	float m_aimPitchTimer; //0x0034 
	D3DXVECTOR2 m_sway; //0x0038 
	float m_DeltaTime; //0x0040 
	char _0x0044[44];
	D3DXMATRIX m_Transform; //0x0070 
	D3DXVECTOR4 m_Position; //0x00B0 
	D3DXVECTOR4 m_View; //0x00C0 
	D3DXVECTOR4 m_Rotation; //0x00D0 
	char _0x00E0[88];
	float m_Fov; //0x0138 
	char _0x013C[24];
	__int64 m_RayResult; //0x0158 
	D3DXVECTOR4 m_RayEnd; //0x0160 
	float m_RayLength; //0x0170 

};//Size=0x0174

class AimAssist
{
public:
	char _0x0000[20];
	float m_yawcopy; //0x0014 
	float m_pitchcopy; //0x0018 
	char _0x001C[68];
	float m_yaw; //0x0060 
	float m_pitch; //0x0064 
	char _0x0068[24];

};//Size=0x0080

class BFServerSettings
{
public:

	enum VoiceChannel
	{
		VoiceChannel_Off = 0,
		VoiceChannel_Team = 1,
		VoiceChannel_Squad = 2,
		VoiceChannel_Loopback = 3,
		VoiceChannel_Count = 4
	};

	char _0x0000[104];
	__int32 m_RoundMaxPlayerCount; //0x0068 
	__int32 m_RoundMinPlayerCount; //0x006C 
	__int32 m_RoundLockdownCountdown; //0x0070 
	__int32 m_RoundRestartCountdown; //0x0074 
	__int32 m_RoundWarmupTimeout; //0x0078 
	char _0x007C[4];
	char* m_pBannerUrl; //0x0080 
	char* m_pServerPreset; //0x0088 
	char* m_pServerType; //0x0090 
	char* m_pServerExperience; //0x0098 
	char* m_pServerDescription; //0x00A0 
	char* m_pServerMessage; //0x00A8 
	char* m_pServerAdministrationSettings; //0x00B0 
	char* m_pServerAdministrationMapRotation; //0x00B8 
	char* m_pServerAdministrationMapRotationInformation; //0x00C0 
	char* m_pSpectators; //0x00C8 
	char* m_pPunkBusterVersion; //0x00D0 
	char* m_pPVZBlazePlaylist; //0x00D8 
	__int32 m_TeamSwitchImbalanceLimit; //0x00E0 
	__int32 m_GameSize; //0x00E4 
	__int32 m_CommanderSize; //0x00E8 
	__int32 m_DeathmatchFriendZoneFallbackCount; //0x00EC 
	char* m_pGameMod; //0x00F0 
	VoiceChannel m_DefaultVoiceChannel; //0x00F8 fb::VoiceChannel 
	__int32 m_DeathmatchFriendZoneFallbackCount2; //0x00FC 
	float m_TeamSwitchCooldownTime; //0x0100 
	__int32 m_ServerConfigurationRefreshInterval; //0x0104 20 
	char* m_pOverrideServerConfigurationStartTime; //0x0108 
	float m_AlternateEORTimeout; //0x0110 
	__int32 m_MaxNumSoldierCorpses; //0x0114 1
	__int32 m_CommanderRankThreshold; //0x0118 
	BYTE m_AutoBalance; //0x011C 
	BYTE m_OverrideAutoBalance; //0x011D 
	BYTE m_DisableBattlePickups; //0x011E 
	BYTE m_IsManDownRotationEnabled; //0x011F 
	BYTE m_IsKillerCameraEnabled; //0x0120 
	BYTE m_MapSequencerEnabled; //0x0121 
	BYTE m_PVZBlazePlaylistEnabled; //0x0122 
	BYTE m_KickAPlayerOnVIPJoin; //0x0123 
	BYTE m_AlwaysAllowedToSpectate; //0x0124 
	char _0x0125[3];

	static BFServerSettings* GetInstance()
	{
		return *(BFServerSettings**)OFFSET_BFSERVERSETTINGS;
	}
}; //Size=0x0128



class ServerSettings
{
public:
	char _0x0000[128];
	float m_VehicleSpawnDelayModifier; //0x0080 
	float m_HumanHealthMultiplier; //0x0084 
	float m_RespawnTimeModifier; //0x0088 
	char _0x008C[4];
	char* m_AdministrationPassword; //0x0090 
	char* m_RemoteAdministrationPort; //0x0098 
	BYTE m_QueryProviderEnabled; //0x00A0 
	BYTE m_DebrisClusterEnabled; //0x00A1 
	BYTE m_VegetationEnabled; //0x00A2 
	BYTE m_WaterPhysicsEnabled; //0x00A3 
	BYTE m_IsDesertingAllowed; //0x00A4 
	BYTE m_IsRenderDamageEvents; //0x00A5 
	BYTE m_RespawnOnDeathPosition; //0x00A6 
	BYTE m_IsStatsEnabled; //0x00A7 
	BYTE m_IsNetworkStatsEnabled; //0x00A8 
	BYTE m_IsAiEnabled; //0x00A9 
	BYTE m_IsDestructionEnabled; //0x00AA 
	BYTE m_IsSoldierAnimationEnabled; //0x00AB 
	BYTE m_IsSoldierDetailedCollisionEnabled; //0x00AC 
	BYTE m_LoadSavePoint; //0x00AD 
	BYTE m_DisableCutscenes; //0x00AE 
	BYTE m_HavokVisualDebugger; //0x00AF 
	BYTE m_HavokCaptureToFile; //0x00B0 
	BYTE m_ShowTriggerDebugText; //0x00B1 
	BYTE m_TimeoutGame; //0x00B2 
	BYTE m_AILooksIntoCamera; //0x00B3 
	BYTE m_DeathmatchDebugInfo; //0x00B4 
	BYTE m_JobEnable; //0x00B5 
	BYTE m_ThreadingEnable; //0x00B6 
	BYTE m_DrawActivePhysicsObjects; //0x00B7 
	BYTE m_IsRanked; //0x00B8 
	BYTE m_UnlockResolver; //0x00B9 
	BYTE m_ScoringLogEnabled; //0x00BA 
	BYTE m_ForcePlaylist; //0x00BB 
	BYTE m_AutoUnspawnBangers; //0x00BC 
	BYTE m_RegulatedAIThrottle; //0x00BD 
	BYTE m_EnableAnimationCulling; //0x00BE 
	BYTE m_FallBackToSquadSpawn; //0x00BF 
	BYTE m_VehicleSpawnAllowed; //0x00C0 
	BYTE m_AdministrationEnabled; //0x00C1 
	BYTE m_AdministrationLogEnabled; //0x00C2 
	BYTE m_AdministrationTimeStampLogNames; //0x00C3 
	BYTE m_AdministrationEventsEnabled; //0x00C4 
	BYTE m_AdministrationServerNameRestricted; //0x00C5 
	char _0x00C6[5];
}; //Size=0x00CB

class PersistenceData
{
public:

	class PersistenceStatGroup
	{
	public:
		char _0x0000[16];
		char* m_pGroupName; //0x0010 
	}; //Size=0x0018

	class PersistenceRetentionPolicy
	{
	public:
		char _0x0000[24];
		__int32 m_DailyHistoryCount; //0x0018 
		__int32 m_WeeklyHistoryCount; //0x001C 
		__int32 m_MonthlyHistoryCount; //0x0020 
		char _0x0024[4];

	}; //Size=0x0028

	char _0x0000[24];
	char* m_pPersistenceName; //0x0018 
	char* m_pClubPersistenceName; //0x0020 
	__int64 m_pValues; //0x0028  
	PersistenceStatGroup* m_pServerDefaultGroup; //0x0030 
	PersistenceStatGroup* m_pClientDefaultGroup; //0x0038 
	PersistenceRetentionPolicy* m_pRetentionPolicy; //0x0040 
	__int64 m_pConsumableMappings; //0x0048 
	BYTE m_DeltaGameReports; //0x0050 
	BYTE m_HistoryDaily; //0x0051 
	BYTE m_HistoryWeekly; //0x0052 
	BYTE m_HistoryMonthly; //0x0053 
	BYTE m_OutputProperties; //0x0054 
	char _0x0055[3];
}; //Size=0x0058


class AwardableTreeBase
{
public:

	class StatCategoryTreeCollection
	{
	public:
		char _0x0000[16];
		char* m_pName; //0x0010 
		__int64 m_pAsset; //0x0018 fb::RefArray<fb::StatCategoriesBaseTree>
	}; //Size=0x0020

	char _0x0000[24];
	StatCategoryTreeCollection* m_pStatCategoryTreeCollection; //0x0018 
	__int64 m_pGeneralCriteria; //0x0020 
	BYTE m_pGeneralStatistics; //0x0028 
	char _0x0029[7];
}; //Size=0x0030

class AwardDataTree : public AwardableTreeBase
{
public:

	class CategorizedAwardData
	{
	public:
		__int64 m_Awards; //0x0000 
		__int64 m_Category; //0x0008 fb::StatsCategoryBaseData* 
		__int64 m_Children; //0x0010 fb::StatsCategoryBaseData* 
		__int64 m_ActivationOrder; //0x0018 fb::AwardActivationOrder* 
	}; //Size=0x0020

	AwardableTreeBase* m_pFilteredAwards; //0x0030 
	CategorizedAwardData* m_pCategorizedAwards; //0x0038 

}; //Size=0x0040

class RankParamsAsset
{
public:
	char _0x0000[32];
	__int32 m_RankLevelCap; //0x0020 
	__int32 m_RankChallengeMapping; //0x0024 
	char _0x0028[4];
	__int32 m_MidLevelMilestoneCount; //0x002C 
	__int32 m_PlayerRanks; //0x0030 
	char _0x0034[12];
	__int64 m_KitRankBuckets; //0x0040 
}; //Size=0x0048

class ScoringData
{
public:

	class ScoringTypeData
	{
	public:
		char _0x0000[16];
		__int32 m_Measuring; //0x0010 fb::StatEvent
		char _0x0014[4];
		__int64 m_pParamX; //0x0018 fb::StatsCategoryBaseData* 
		__int64 m_pParamY; //0x0020 fb::StatsCategoryBaseData*
		float m_Limit; //0x0028 
		char _0x002C[4];
		char* m_pDescriptionSid; //0x0030 
		__int32 m_VisibilityType; //0x0038 fb::ScoringVisibilityType
		__int32 m_Bucket; //0x003C fb::ScoringBucket
		float m_Score; //0x0040
		float m_AdditionalValueMultiplier; //0x0044 
		BYTE m_ShowForTeam; //0x0048 
		char _0x0049[7];
	};//Size=0x0050

	char _0x0000[24];
	ScoringTypeData** m_ppScoringTypes; //0x0018 fb::RefArray<fb::ScoringTypeData> 
	__int64 m_ppScoringHandlers; //0x0020 fb::RefArray<fb::ScoringHandlerData> 
	__int64 m_ppBuckets; //0x0028 fb::RefArray<fb::ScoringBucketData> 
}; //Size=0x0030

class BattlePackAsset
{
public:
	char _0x0000[24];
	__int64 m_pBattlePackInfos; //0x0018 
	__int64 m_pBoostItems; //0x0020 
	__int64 m_pBoosts; //0x0028 
	__int64 m_pUnlockInfos; //0x0030 
	__int64 m_pPremiumIds; //0x0038 
	__int64 m_pVeteranIds; //0x0040 
	__int64 m_pWeaponIds; //0x0048 
}; //Size=0x0050

class StaticUnlockList
{
public:
	char _0x0000[24];
	char* m_pUnlockInfos; //0x0018 
}; //Size=0x0020

class StatSpamSettings
{
public:
	char _0x0000[24];
	__int64 m_pSpamList; //0x0018 
}; //Size=0x0020

class PlayerTypeProfile
{
public:
	char _0x0000[16];
	char* m_pAssetName; //0x0010 
	PersistenceData* m_pValues; //0x0018 
	AwardDataTree* m_pAwards; //0x0020 
	RankParamsAsset* m_pRankParams; //0x0028 
	ScoringData* m_pScoring; //0x0030 
	__int64 m_pDogTags; //0x0038 
	BattlePackAsset* m_pBattlePacks; //0x0040 
	__int64 m_pSkillLevelParams; //0x0048 
	StaticUnlockList* m_pStaticUnlocks; //0x0050 
	StatSpamSettings* m_SpamSettings; //0x0058 
	StatSpamSettings* m_OrderedUnlockNames; //0x0060 
}; //Size=0x0068

class PointSystemParamsAsset
{
public:
	char _0x0000[24];
	float m_MultiKillTimeLimit; //0x0018 
	float m_TimedKillStreakMinTime; //0x001C 
	float m_TimedKillStreakMaxTime; //0x0020 
	float m_DnfTimeout; //0x0024 
	__int32 m_KillStreakX; //0x0028 
	__int32 m_NemesisKillX; //0x002C 
	float m_AdrenalineKillHealthLimit; //0x0030 
	char _0x0034[4];
	__int64 m_KillStreakThresholds; //0x0038 
	float m_UnanimousSupportThreshold; //0x0040 
	float m_UnanimousSupportTickTime; //0x0044 
}; //Size=0x0048

class PersistenceConfiguration
{
public:
	char _0x0000[24];
	PlayerTypeProfile* m_pMPProfile; //0x0018 
	PlayerTypeProfile* m_pSPProfile; //0x0020 
	PlayerTypeProfile* m_pCoopProfile; //0x0028 
	PointSystemParamsAsset* m_PointSystemParams; //0x0030 
	__int64 m_XdpExport; //0x0038 null
}; //Size=0x0040

class BFDedicatedServerSettings
{
public:
	char _0x0000[32];
	PersistenceConfiguration* m_pPersistenceConfig; //0x0020 

	static BFDedicatedServerSettings* GetInstance()
	{
		return *reinterpret_cast<BFDedicatedServerSettings**>(OFFSET_BFDedicatedServerSettings);
	}

	void DumpScoringData()
	{
		FILE* pFile = fopen("D:\\pvz_scoring.txt", "w");

		PersistenceConfiguration* pConfig = m_pPersistenceConfig;
		if (!IsValidPtr(pConfig))
			return;
		
		PlayerTypeProfile* pProfile = pConfig->m_pMPProfile;
		if (!IsValidPtr(pProfile))
			return;
		
		ScoringData* pScoring = pProfile->m_pScoring;
		if (!IsValidPtr(pScoring))
			return;

		ScoringData::ScoringTypeData** ppTypes=pScoring->m_ppScoringTypes;
		

		for (int i = 0; ppTypes[i] != 0; i++)
		{
			//printf( "Name: %s Score: %2.1f Additional Multiplier %2.1f\n", ppTypes[i]->m_pDescriptionSid, ppTypes[i]->m_Score, ppTypes[i]->m_AdditionalValueMultiplier );

			fprintf(pFile, "Name: %s Score: %2.1f Additional Multiplier %2.1f\n", ppTypes[i]->m_pDescriptionSid, ppTypes[i]->m_Score, ppTypes[i]->m_AdditionalValueMultiplier);
		}

		fclose(pFile);
	}
};
class ClientAntAnimatableComponent
{
public:
	virtual __int64 getType();
	char _0x0000[288];
	Animatable* m_animatable; //0x0128 
};
class Effect
{
public:

	class MovementSpeedBuffEffectData
	{
	public:
		char _0x0000[16];
		float m_MinPowerMultiplier; //0x0010 
		float m_MaxPowerMultiplier; //0x0014 
		float m_MinPowerThreshold; //0x0018 
		float m_MaxPowerThreshold; //0x001C 
		BYTE m_IgnoreWeaponUpgrades; //0x0020 
		char _0x0021[7];
	}; //Size=0x0028

	char _0x0000[40];
	MovementSpeedBuffEffectData* m_pData; //0x0028 
	char _0x0030[72];

}; //Size=0x0078

class ClientCharacterEntity
{
public:

	

	virtual void Function1();

	char _0x0008[40];
	__int64 m_pCharacterPhysics; //0x0030 fb::CharacterPhysicsEntity* 
	char _0x0038[24];
	ClientPlayer* m_pPlayer; //0x0050
	ClientAntAnimatableComponent* m_pAnimatableComponent[2]; //0x0058 
	char _0x0068[8];
	__int64 m_pCharacterRender; //0x0070 fb::ClientCharacterEntityRenderComponent* 
	char _0x0078[8];
	__int64 m_pEffect; //0x0080 this class is actually just garbage
	char _0x0088[64];
	__int64 m_pViewFxData; //0x00C8 Disabled
	char _0x00D0[16];
	__int64 m_pSoldierCamera; //0x00E0 
	char _0x00E8[56];
	__int64 m_pCustomizationComponent; //0x0120 fb::ClientPVZSoldierCustomizationComponent 
	char _0x0128[32];
	__int64 m_pSoldierData; //0x0148 fb::PvzSoldierEntityData*
	char _0x0150[384];
}; //Size=0x02D0

class PeaShooter1
{
public:
	Peashooter2* m_class2; //0x0000 

	static PeaShooter1* GetInstance()
	{
		return (PeaShooter1*)0x141c15250;
	}
};//Size=0x0008

class Peashooter2
{
public:
	char _0x0000[104];
	PVZVisualUnlockasset* m_PVZVisualUnlockAsset; //0x0068 PVZVisualUnlockAsset

};//Size=0x0070

class PVZVisualUnlockasset
{
public:
	char _0x0000[1584];
	Class3* m_Class3; //0x0630 

};//Size=0x0638

class Class3
{
public:
	char _0x0000[208];
	MovementSpeedBuffEffectData* m_MovementBuffData; //0x00D0 MovementSpeedBuffEffectData
	char _0x00D8[1128];
	Class4* m_class4; //0x0540 

};//Size=0x0548

class Class4
{
public:
	char _0x0000[56];
	ResetAbilityBuffEffectData* m_ResetAbility; //0x0038 ResetAbilityBuffEffectData

};//Size=0x0040

class ResetAbilityBuffEffectData
{
public:
	char _0x0000[352];
	MovementSpeedBuffEffectData* m_MovementBuffData; //0x0160 MovementSpeedBuffEffectData
	JumpHeightBuffEffectData* m_JumpHeight; //0x0168 JumpHeightBuffEffectData

};//Size=0x0170

class MovementSpeedBuffEffectData
{
public:
	char _0x0000[16];
	float m_MinPowerMultiplier; //0x0010 
	float m_MaxPowerMultiplier; //0x0014 
	float m_MinPowerThreshold; //0x0018 
	float m_MaxPowerThreshold; //0x001C 

};//Size=0x0020

class JumpHeightBuffEffectData
{
public:
	char _0x0000[16];
	float m_MinPowerMultiplier; //0x0010 
	float m_MaxPowerMultiplier; //0x0014 
	float m_MinPowerThreshold; //0x0018 
	float m_MaxPowerThreshold; //0x001C 

};//Size=0x0020

class PlayerEntryComponentData
{
public:
	char _0x0000[216];
	__int32 m_TriggerEventOkay; //0x00D8 
	BYTE m_ForbiddenForHuman; //0x00DC 
	BYTE m_IsAllowedToExitInAir; //0x00DD 
	BYTE m_IsShielded; //0x00DE 
	BYTE m_LockSoldierAimingToEntry; //0x00DF 
	BYTE m_ShowSoldierInEntry; //0x00E0 
	BYTE m_Show1pSoldierInEntry; //0x00E1 
	BYTE m_StancesEnabled; //0x00E2 
	BYTE m_ShowSoldierWeaponInEntry; //0x00E3 
	BYTE m_Show1pSoldierInEntryForPlayerOnly; //0x00E4 
	BYTE m_Show3pSoldierWeaponInEntry; //0x00E5 
	BYTE m_ShowSoldierGearInEntry; //0x00E6 
	char __0x00E7[3]; //0x00E7 
	BYTE m_AllowRagdollFromEntry; //0x00EA 
};//Size=0x00EB

class ClientPlayerEntryComponent
{
public:
	char _0x0000[16];
	PlayerEntryComponentData* m_data; //0x0010 PlayerEntryComponentData
	char _0x0018[104];
};//Size=0x0080

class ClientSoldierBodyComponent
{
public:
	char _0x0000[16];
	SoldierBodyComponentData* m_data; //0x0010 SoldierBodyComponentData
	char _0x0018[8];
	ClientPlayerEntryComponent* m_EntryComp; //0x0020 ClientPlayerEntryComponent

};//Size=0x0028

class SoldierBodyComponentData
{
public:
	char _0x0000[112];
	float m_OverrideGravityValue; //0x0070 
	float m_OverrideVelocityY; //0x0074 
	float m_SprintMultiplier; //0x0078 
	BYTE m_OverideGravity; //0x007C 
	BYTE m_OverideVelocity; //0x007D 
	BYTE m_DisableParachute; //0x007E 
	BYTE m_PronePoseEnabled; //0x007F 

};//Size=0x0080