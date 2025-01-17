#include "stdafx.h"
#include "Loading.h"
#include "Management.h"

#include "Sky.h"
#include "TexEffect.h"
#include "MeshEffect.h"
#include "Player.h"
#include "HPBack.h"
#include "TestMonster.h"
#include "Weapon.h"
#include "Dummy_Target.h"
#include "Trail_VFX.h"

#include "UI_Manager.h"

#include "TestMonster.h"
#include "PoisonButterfly.h"
#include "BlackUrchin.h"
#include "BlackWolf.h"
#include "Genji.h"

#include "PlayerHP.h"
#include "PlayerST.h"
#include "BossDecoUI.h"
#include "BossHP.h"

#include "Expendables.h"
#include "Material.h"
#include "Armor.h"

USING(Client)

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	ZeroMemory(m_szString, sizeof(_tchar) * 128);
	Safe_AddRef(m_pGraphicDev);	
}

HRESULT CLoading::Ready_Loading(SCENEID eLoadingID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	m_eLoadingID = eLoadingID;

	return S_OK;
}

_uint CLoading::Loading_ForStage(void)
{
	// BT_Node 생성 중
	if (FAILED(g_pManagement->Ready_BT_Node()))
		return E_FAIL;

	_mat DefaultMat;
	D3DXMatrixIdentity(&DefaultMat);

	// 이펙트 원형 생성
	Ready_Effect();

	// Sky
	//if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Sky", CSky::Create(m_pGraphicDev))))
	//	return E_FAIL;

	// UI 원형 생성
	if (FAILED(CUI_Manager::Get_Instance()->Add_UI_Prototype(m_pGraphicDev)))
		return E_FAIL;
	
	// Item 원형 생성
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Expendables", CExpendables::Create(m_pGraphicDev))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Material", CMaterial::Create(m_pGraphicDev))))
		return E_FAIL;
	
	// 오브젝트 원형 생성
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 플레이어
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Player", CPlayer::Create(m_pGraphicDev))))
		return E_FAIL;

	//몬스터

	if (FAILED(g_pManagement->Add_Prototype(L"Monster_TestMonster", CTestMonster::Create(m_pGraphicDev))))
		return E_FAIL;
	// 독나방
	if (FAILED(g_pManagement->Add_Prototype(L"Monster_PoisonButterfly", CPoisonButterfly::Create(m_pGraphicDev))))
		return E_FAIL;
	// 검은 성게
	if (FAILED(g_pManagement->Add_Prototype(L"Monster_BlackUrchin", CBlackUrchin::Create(m_pGraphicDev))))
		return E_FAIL;
	// 검은 늑대
	if (FAILED(g_pManagement->Add_Prototype(L"Monster_BlackWolf", CBlackWolf::Create(m_pGraphicDev))))
		return E_FAIL;

	//무기
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Weapon", CWeapon::Create(m_pGraphicDev))))
		return E_FAIL;

	//더미
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_Dummy", CDummy_Target::Create(m_pGraphicDev))))
		return E_FAIL;

	// 트레일
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_SwordTrail", Engine::CTrail_VFX::Create(m_pGraphicDev))))
		return E_FAIL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_bFinish = true;

	cout << "로딩 완료" << endl;

	return 0;
}

unsigned int CALLBACK CLoading::Thread_Main(void* pArg)
{
	CLoading*	pLoading = (CLoading*)pArg;

	_uint		iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case SCENE_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	return iFlag;
}

HRESULT CLoading::Ready_Effect(void)
{
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_FootSmoke", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Player_FootSmoke.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_ButterFly_SoftSmoke", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/ButterFly_SoftSmoke.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_ButterFly_PointParticle", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/ButterFly_PointParticle.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_ButterFly_VenomShot", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/ButterFly_VenomShot.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_ButterFly_RingLine", CMeshEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/ButterFly_RingLine.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_ButterFly_Distortion", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/ButterFly_Distortion.dat")))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_Blood_0", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_Blood_0.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_Blood_1", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_Blood_1.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_Blood_2", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_Blood_2.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodMist_0", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodMist_0.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodMist_1", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodMist_1.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodParticle_0", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodParticle_0.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodParticle_1", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodParticle_1.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodParticle_2", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodParticle_2.dat")))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"Effect_Hit_BloodParticle_3", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/Hit_BloodParticle_3.dat")))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"SpawnParticle", CTexEffect::Create(m_pGraphicDev, Read_EffectData(L"../../Data/EffectData/SpawnParticle.dat")))))
		return E_FAIL;
	
	return S_OK;
}

Engine::EFFECT_INFO* CLoading::Read_EffectData(const _tchar* szPath)
{
	HANDLE hFile = CreateFile(szPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		::MSG_BOX("Load Failed. [INVALID_HANDLE_VALUE]");

	DWORD dwByte = 0;
	Engine::EFFECT_INFO* pInfo = new Engine::EFFECT_INFO;

	_bool bIsTex = false;
	::ReadFile(hFile, &bIsTex, sizeof(_bool), &dwByte, nullptr);

	while (true)
	{
		::ReadFile(hFile, &pInfo->bBillBoard, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bOnlyYRot, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bDistortion, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bStaticFrame, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bUseColorTex, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bUseRGBA, sizeof(_bool), &dwByte, nullptr);

		::ReadFile(hFile, &pInfo->bColorMove, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bDirMove, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bFadeIn, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bFadeOut, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bLinearMove, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bRandomMove, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bRandomRot, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bRandStartPos, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bRevColor, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bRotMove, sizeof(_bool), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->bScaleMove, sizeof(_bool), &dwByte, nullptr);

		::ReadFile(hFile, &pInfo->fAlphaSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fAlphaSpeed_Max, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fAlphaSpeed_Min, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fColorSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fCreateDelay, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fCreateDelay_Max, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fCreateDelay_Min, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fLifeTime, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMaxAlpha, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fAnimSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMaxFrame, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMoveScaleSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMoveSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMoveSpeed_Max, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMoveSpeed_Min, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fRandStartPosRange_Max, sizeof(_float) * 3, &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fRandStartPosRange_Min, sizeof(_float) * 3, &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fRotSpeed, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fRotSpeed_Max, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fRotSpeed_Min, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->iMaxCount, sizeof(_int), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->szColorName, sizeof(TCHAR) * MAX_STR, &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->szName, sizeof(TCHAR) * MAX_STR, &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->szGradientName, sizeof(TCHAR) * MAX_STR, &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vEndColor, sizeof(_v4), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vMoveDirection, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vMoveScale, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vRandDirectionRange, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vRotDirection, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vStartColor, sizeof(_v4), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vStartPos, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->vStartScale, sizeof(_v3), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fColorIndex, sizeof(_float), &dwByte, nullptr);
		::ReadFile(hFile, &pInfo->fMaskIndex, sizeof(_float), &dwByte, nullptr);

		break;
	}

	CloseHandle(hFile);

	return pInfo;
}

HRESULT CLoading::Stage_Object_Ready()
{
	return NOERROR;
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, SCENEID eLoadingID)
{
	CLoading*	pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eLoadingID)))
		Engine::Safe_Release(pInstance);
	
	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}

