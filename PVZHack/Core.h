#define CoderTag "0x31,0x79,0x74,0x1f,0x7c,0x56,0x5e,0x5d,0x43,0x75,0x1b,0x3a,0x4a,0x01,0x42,0x18,0x0f,0x7d,0x4b,0x54,0x55,0x57,0x44,0x41,0x0c,0x4e,0x3c,0x43,0x53"
#define DecodeKey "a/.?1#2)*=zY!!"

class Core
{
public:
	Core()
	{
		m_FOV = 10;
	}
	void CheckPlayerLife()
	{
		LastFramePlayerWasDead = CurrentFramePlayerIsDead;
		GameContext* pContext = GameContext::GetInstance();
		if (!IsValidPtr(pContext))
			return;

		PlayerManager* pPlayerManager = pContext->m_PlayerManager;
		if (!IsValidPtr(pPlayerManager))
			return;

		ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
		if (!IsValidPtr(pLocalPlayer))
			return;

		ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
		if (!IsValidPtr(pLocalSoldier))
			return;

		if (Helpers::IsAlive(pLocalSoldier))
		{
			CurrentFramePlayerIsDead = false;
			return;
		}

		CurrentFramePlayerIsDead = true;
	}
	void NoRecoil()
	{
		GameContext* pContext = GameContext::GetInstance();
		if (!IsValidPtr(pContext))
			return;

		PlayerManager* pPlayerManager = pContext->m_PlayerManager;
		if (!IsValidPtr(pPlayerManager))
			return;

		ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
		if (!IsValidPtr(pLocalPlayer))
			return;

		ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
		if (!IsValidPtr(pLocalSoldier))
			return;

		if (CurrentFramePlayerIsDead) return;

		ClientPVZSoldierWeaponsComponent* pWepComp = pLocalSoldier->m_ClientSoldierWeaponsComp;
		if (!IsValidPtr(pWepComp))
			return;

		PVZWeapon* pWep = pWepComp->m_WeaponComponent;
		if (!IsValidPtr(pWep))
			return;

		PVZWeaponFiringData* pWepData = pWep->m_data;
		if (!IsValidPtr(pWepData))
			return;

		GunSwayData* pSway = pWepData->m_SwayData;
		if (!IsValidPtr(pSway))
			return;

		pSway->m_DeviateScaleFactorZoom = 0.0f;
		pSway->m_DeviationScaleFactorNoZoom = 0.0f;
		pSway->m_FirstShotMultiplier = 0.0f;
		pSway->m_GameplayDeviationFactorZoom = 0.0f;
		pSway->m_GameplayDeviationScaleFactorNoZoom = 0.0f;
		pSway->m_ShootingRecoilDecreaseScale = 10000.0f;
	}
	void DamageMod()
	{
		try
		{
			GameContext* pContext = GameContext::GetInstance();
			if (!IsValidPtr(pContext))
				return;

			PlayerManager* pPlayerManager = pContext->m_PlayerManager;
			if (!IsValidPtr(pPlayerManager))
				return;

			ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
			if (!IsValidPtr(pLocalPlayer))
				return;

			ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
			if (!IsValidPtr(pLocalSoldier))
				return;

			if (CurrentFramePlayerIsDead) return;

			ClientPVZSoldierWeaponsComponent* pWepComp = pLocalSoldier->m_ClientSoldierWeaponsComp;
			if (!IsValidPtr(pWepComp))
				return;

			PVZWeapon* pWep = pWepComp->m_WeaponComponent;
			if (!IsValidPtr(pWep))
				return;

			PVZWeaponFiringData* pWepData = pWep->m_data;
			if (!IsValidPtr(pWepData))
				return;

			FiringFunctionData* pFFD = pWepData->m_PrimaryFire;
			if (!IsValidPtr(pFFD))
				return;

			ShotConfigData ShotConfig = pFFD->m_Shot;

			BulletEntityData* pBulletEntData = ShotConfig.m_pProjectileData;
			if (!IsValidPtr(pBulletEntData))
				return;

			pBulletEntData->m_StartDamage = 9999.0f;
			pBulletEntData->m_EndDamage = 9998.0f;
			pBulletEntData->m_TimeToLive = 15.0f;
		}
		catch (...){
			std::cout << "SEH Exception Thrown in DamageMod \n";
		}
	}
	void RenderFrame()
	{
		DebugRenderer* pDebugRenderer = DebugRenderer::GetInstance();
		if (!IsValidPtr(pDebugRenderer))
			return;

		Screen* pScreen = Helpers::GetScreen();
		if (!IsValidPtr(pScreen))
			return;

		float height = pScreen->m_WindowHeight;
		float width = pScreen->m_WindowWidth;

		pDebugRenderer->RenderText(width/2, 0.0f, Color32(255, 255, 255, 255).GetColor(), "%s", HexDecrypt(CoderTag,DecodeKey).c_str());

		GameContext* pContext = GameContext::GetInstance();
		if (!IsValidPtr(pContext))
			return;

		PlayerManager* pPlayerManager = pContext->m_PlayerManager;
		if (!IsValidPtr(pPlayerManager))
			return;

		ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
		if (!IsValidPtr(pLocalPlayer))
			return;

		ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
		if (!IsValidPtr(pLocalSoldier))
			return;

		if (CurrentFramePlayerIsDead) return;

		int MaxPlayers = pPlayerManager->m_MaxPlayerCount;
		for (int i = 0; i < MaxPlayers; i++)
		{
			ClientPlayer* pEnemy = pPlayerManager->At(i);
			if (!IsValidPtr(pEnemy))
				continue;

			if (pEnemy->m_TeamID == pLocalPlayer->m_TeamID)
				continue;

			ClientPVZSoldierEntity* pEnemySoldier = pEnemy->m_ClientSoldierEntity;
			if (!IsValidPtr(pEnemySoldier))
				continue;

			if (!Helpers::IsAlive(pEnemySoldier) /*|| !Helpers::UpdateBones(pEnemySoldier)*/)
				continue;

			Vec3 TempBone, TopTemp, BottomTemp, Bone, BoneTop, BoneBottom;
			//if (!Helpers::GetBone(pEnemySoldier, &TempBone, 8))
			//continue;

			ClientSoldierPrediction* pPredictionController = pEnemySoldier->m_PredictedController;
			if (!IsValidPtr(pPredictionController))
				continue;

			TempBone = pPredictionController->m_Position;
			TopTemp = TempBone;
			BottomTemp = TempBone;
			TopTemp.y += 1.5f;
			TopTemp.x += .8f;

			if (!Helpers::WorldToScreen(TempBone, Bone))
				continue;

			if (!Helpers::WorldToScreen(BottomTemp, BoneBottom))
				continue;

			if (!Helpers::WorldToScreen(TopTemp, BoneTop))
				continue;

			
			Vec3 SnapLineStart;
			SnapLineStart.x = width / 2;
			SnapLineStart.y = height - (height*.05f);

			DWORD Color = pEnemySoldier->m_Occluded ? Color32(0, 0, 255, 255).GetColor() : Color32(0, 255, 0, 255).GetColor();
			pDebugRenderer->RenderText(Bone.x, Bone.y, Color, pEnemySoldier->m_EntityName);
			pDebugRenderer->DrawLine(SnapLineStart.x, SnapLineStart.y, Bone.x, Bone.y, Color);

			if (Box3D)
			{
				CharacterPhysicsEntity* pPhysicsEnt = pPredictionController->m_CharacterPhysicsEntity;
				if (!IsValidPtr(pPhysicsEnt))
					return;

				CharacterPhysicsEntityCollisionShapes* pColShapes = pPhysicsEnt->m_CollisionShapes;
				if (!IsValidPtr(pColShapes))
					return;

				AxisAlignedBB2 AABB;
				Helpers::TransformAABB(pColShapes->m_aabbs[0], AABB, TempBone);
				Helpers::DrawAABB(AABB, pDebugRenderer, Color);
			}else{
				pDebugRenderer->DrawLineRect(BoneBottom.x, BoneTop.y, abs(BoneBottom.x - BoneTop.x), abs(BoneBottom.y - BoneTop.y), Color);
			}

		}
	}
	void Aimbot()
	{
		DebugRenderer* pDebugRenderer = DebugRenderer::GetInstance();
		if (!IsValidPtr(pDebugRenderer))
			return;

		GameContext* pContext = GameContext::GetInstance();
		if (!IsValidPtr(pContext))
			return;

		PlayerManager* pPlayerManager = pContext->m_PlayerManager;
		if (!IsValidPtr(pPlayerManager))
			return;


		ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
		if (!IsValidPtr(pLocalPlayer))
			return;

		ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
		if (!IsValidPtr(pLocalSoldier))
			return;

		if (CurrentFramePlayerIsDead) return;

		DxRenderer* pDXRenderer = DxRenderer::GetInstance();
		if (!IsValidPtr(pDXRenderer))
			return;

		Screen* pScreen = pDXRenderer->m_pScreen;
		if (!IsValidPtr(pScreen))
			return;

		GameRenderer* pGameRenderer = GameRenderer::GetInstance();
		if (!IsValidPtr(pGameRenderer))
			return;

		RenderView* pRenderView = pGameRenderer->m_pRenderView;
		if (!IsValidPtr(pRenderView))
			return;

		ClientPVZSoldierWeaponsComponent* pWeaponComp = pLocalSoldier->m_ClientSoldierWeaponsComp;
		if (!IsValidPtr(pWeaponComp))
			return;

		WeaponHandler* pWepHandler = pWeaponComp->m_WepHandler;
		if (!IsValidPtr(pWepHandler))
			return;

		ClientPVZSoldierWeapon* pWeapon = pWepHandler->m_SoldierWeapon;
		if (!IsValidPtr(pWeapon))
			return;

		ClientSoldierWeapon* pSoldierWeapon = pWeapon->m_pClientWep;
		if (!IsValidPtr(pSoldierWeapon))
			return;
		D3DXMATRIX LocalMat;
		D3DXMATRIX SPmat = pSoldierWeapon->m_ShootSpace;
		Vec3 shootspaceforward = Vec3(SPmat._31, SPmat._32, SPmat._33);
		pLocalSoldier->GetTransform(&LocalMat);
		Vec3 LocalPos = Vec3(LocalMat._41, LocalMat._42, LocalMat._43);

		float closestdistance = 9999.0f;
		ClientPlayer* ClosestClient = NULL;
		ClientPVZSoldierEntity* ClosestSoldier = NULL;
		Vec3 EnemyAimVecWorld, EnemyAimVecScreen;
		int ClosestPlayerIndex = 0;

		int MaxPlayers = pPlayerManager->m_MaxPlayerCount;
		for (int i = 0; i < MaxPlayers; i++)
		{
			ClientPlayer* pEnemy = pPlayerManager->At(i);
			if (!IsValidPtr(pEnemy))
				continue;

			if (pEnemy->m_TeamID == pLocalPlayer->m_TeamID)
				continue;

			ClientPVZSoldierEntity* pEnemySoldier = pEnemy->m_ClientSoldierEntity;
			if (!IsValidPtr(pEnemySoldier))
				continue;

			if (!Helpers::IsAlive(pEnemySoldier) /*|| !Helpers::UpdateBones(pEnemySoldier)*/)
				continue;

			if (pEnemySoldier->m_Occluded)
				continue;;

			Vec3 TempAimVec, TargetVec;
			ClientSoldierPrediction* pPredictionController = pEnemySoldier->m_PredictedController;
			if (!IsValidPtr(pPredictionController))
				continue;

			ClientSoldierCameraComponent* pCameraComp = pEnemySoldier->m_CameraComponent;
			if (!IsValidPtr(pCameraComp))
				continue;

			TempAimVec = pPredictionController->m_Position;

			if (!Helpers::IsInFOV(shootspaceforward, TempAimVec, LocalPos, m_FOV))
				continue;

			if (!Helpers::WorldToScreen(TempAimVec, TargetVec))
				continue;

			float ScreenX = pScreen->m_WindowWidth / 2;
			float ScreenY = pScreen->m_WindowHeight / 2;

			float PosX = abs(TargetVec.x - ScreenX);
			float PosY = abs(TargetVec.y - ScreenY);

			float flScreenDistance = sqrt(PosX*PosX + PosY*PosY);
			if (flScreenDistance < closestdistance)
			{
				ClosestClient = pEnemy;
				ClosestSoldier = pEnemySoldier;
				closestdistance = flScreenDistance;
				EnemyAimVecWorld = TempAimVec; //temp aimvec is still in world coords
				EnemyAimVecScreen = TargetVec;
				ClosestPlayerIndex = i;
			}
		}
		ClientSoldierCameraComponent* pCamComp = pLocalSoldier->m_CameraComponent;
		if (!IsValidPtr(pCamComp))
			return;

		ClientSoldierPrediction* pPredictionController = pLocalSoldier->m_PredictedController;
		if (!IsValidPtr(pPredictionController))
			return;

		if (!IsValidPtr(ClosestClient) || !IsValidPtr(ClosestSoldier))
			return;

		ClientSoldierPrediction* pEnemyPredicted = ClosestSoldier->m_PredictedController;
		if (!IsValidPtr(pEnemyPredicted))
			return;

		PVZWeapon* pWep = pWeaponComp->m_WeaponComponent;
		if (!IsValidPtr(pWep))
			return;

		PVZWeaponFiringData* pWepData = pWep->m_data;
		if (!IsValidPtr(pWepData))
			return;

		FiringFunctionData* pFFD = pWepData->m_PrimaryFire;
		if (!IsValidPtr(pFFD))
			return;

		ShotConfigData ShotConfig = pFFD->m_Shot;

		BulletEntityData* pBulletData = ShotConfig.m_pProjectileData;
		if (!IsValidPtr(pBulletData))
			return;

		ClientSoldierAimingSimulation* pAimSim = pWeapon->m_pAuthorativeAiming;
		if (!IsValidPtr(pAimSim))
			return;

		AimAssist* pAimAssist = pAimSim->m_fpsAimer;
		if (!IsValidPtr(pAimAssist))
			return;

		EnemyAimVecWorld.y += 1.0f;
		D3DXMATRIX mat = pRenderView->m_viewMatrixInverse;
		Vec3 LocalOrigin = Vec3(mat._41, mat._42, mat._43);

		float distance = Helpers::VectorLength3D((EnemyAimVecWorld - LocalOrigin));
		Helpers::AimCorrection(LocalOrigin, EnemyAimVecWorld, Vec3(0.0f, 0.0f, 0.0f), pEnemyPredicted->m_Velocity, EnemyAimVecWorld, distance, ShotConfig.m_InitialSpeed.z, pBulletData->m_Gravity);

		Vec3 DeltaVector = EnemyAimVecWorld - LocalOrigin;
		DeltaVector.normalize();

		float flYaw = -atan2(DeltaVector.x, DeltaVector.z);  //x
		float flPitch = atan2(DeltaVector.y, Helpers::VectorLength2D(DeltaVector)); //y

		float YawDelta = pAimSim->m_sway.x;
		float PitchDelta = pAimSim->m_sway.y;
		pAimAssist->m_yawcopy = (flYaw - YawDelta);
		pAimAssist->m_pitchcopy = (flPitch - PitchDelta);
	}
	void SpeedMod()
	{
		GameContext* pContext = GameContext::GetInstance();
		if (!IsValidPtr(pContext))
			return;

		PlayerManager* pPlayerManager = pContext->m_PlayerManager;
		if (!IsValidPtr(pPlayerManager))
			return;

		ClientPlayer* pLocalPlayer = pPlayerManager->m_LocalPlayer;
		if (!IsValidPtr(pLocalPlayer))
			return;

		ClientPVZSoldierEntity* pLocalSoldier = pLocalPlayer->m_ClientSoldierEntity;
		if (!IsValidPtr(pLocalSoldier))
			return;

		if (CurrentFramePlayerIsDead) return;

		if (!(strcmp(pLocalSoldier->m_EntityName, "peashooter") == 0))
			return;

		PeaShooter1* pShooter = PeaShooter1::GetInstance();
		if (!IsValidPtr(pShooter))
			return;

		Peashooter2* pShooter2 = pShooter->m_class2;
		if (!IsValidPtr(pShooter2))
			return;

		PVZVisualUnlockasset* pAsset = pShooter2->m_PVZVisualUnlockAsset;
		if (!IsValidPtr(pAsset))
			return;

		Class3* pShooter3 = pAsset->m_Class3;
		if (!IsValidPtr(pShooter3))
			return;

		Class4* pShooter4 = pShooter3->m_class4;
		if (!IsValidPtr(pShooter4))
			return;

		ResetAbilityBuffEffectData* pBuffEffect = pShooter4->m_ResetAbility;
		if (!IsValidPtr(pBuffEffect))
			return;

		MovementSpeedBuffEffectData* pSpeedData = pBuffEffect->m_MovementBuffData;
		if (!IsValidPtr(pSpeedData))
			return;

		JumpHeightBuffEffectData* pJumpData = pBuffEffect->m_JumpHeight;
		if (!IsValidPtr(pJumpData))
			return;

		pSpeedData->m_MaxPowerMultiplier = 3.0f;
		pJumpData->m_MaxPowerMultiplier = 12.0f;
	}
	void XPMod()
	{
		BFDedicatedServerSettings* pServer = BFDedicatedServerSettings::GetInstance();
		if (!IsValidPtr(pServer))
			return;

		PersistenceConfiguration* pConfig = pServer->m_pPersistenceConfig;
		if (!IsValidPtr(pConfig))
			return;

		PlayerTypeProfile* pProfile = pConfig->m_pMPProfile;
		if (!IsValidPtr(pProfile))
			return;

		ScoringData* pScoring = pProfile->m_pScoring;
		if (!IsValidPtr(pScoring))
			return;

		ScoringData::ScoringTypeData** ppTypes = pScoring->m_ppScoringTypes;

		for (int i = 0; i < 116; i++)
		{
			ppTypes[i]->m_Score = XP;
		}
	}
	bool GetLastFrameLife()
	{
		return LastFramePlayerWasDead;
	}
	bool GetCurrentFrameLife()
	{
		return CurrentFramePlayerIsDead;
	}
	int m_FOV;
	float XP;
	bool Box3D = true;

	//Public is easier than mutate and accessor methods
private:
	bool LastFramePlayerWasDead = true;
	bool CurrentFramePlayerIsDead = true;
};