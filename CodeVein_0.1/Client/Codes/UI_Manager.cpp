#include "stdafx.h"
#include "..\Headers\UI_Manager.h"

#include "Button_UI.h"
#include "HPBack.h"
#include "PlayerHP.h"
#include "PlayerST.h"
#include "BossDecoUI.h"
#include "BossHP.h"

#include "QuickSlot.h"


//////////////////
#include "Expendables_Inven.h"
#include "Expendables_Slot.h"
#include "Select_UI.h"
#include "Material_Inven.h"
#include "Material_Slot.h"
#include "Weapon_Slot.h"
#include "Weapon_Inven.h"
#include "Armor_Slot.h"
#include "Armor_Inven.h"
/////////////////


IMPLEMENT_SINGLETON(CUI_Manager)

CUI_Manager::CUI_Manager()
{
}

CUI_Manager::~CUI_Manager()
{
	Free();
}

HRESULT CUI_Manager::Add_UI_Prototype(_Device pDevice)
{
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_HPBack", CHPBack::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_PlayerHP", CPlayerHP::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_PlayerST", CPlayerST::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_BossDecoUI", CBossDecoUI::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_BossHP", CBossHP::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_ButtonUI", CButton_UI::Create(pDevice))))
		return E_FAIL;

	

	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_QuickSlot", CQuickSlot::Create(pDevice))))
		return E_FAIL;
	////////////////////////////////////////////////////////////////////////////////////////////



	
	//////////////////////////////////////////////////////////
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_SelectUI", CSelect_UI::Create(pDevice))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_ExpendSlot", CExpendables_Slot::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_ExpendablesInven", CExpendables_Inven::Create(pDevice))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_MaterialSlot", CMaterial_Slot::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_MaterialInven", CMaterial_Inven::Create(pDevice))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_WeaponSlot", CWeapon_Slot::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_WeaponInven", CWeapon_Inven::Create(pDevice))))
		return E_FAIL;

	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_ArmorSlot", CArmor_Slot::Create(pDevice))))
		return E_FAIL;
	if (FAILED(g_pManagement->Add_Prototype(L"GameObject_ArmorInven", CArmor_Inven::Create(pDevice))))
		return E_FAIL;

	return NOERROR;
}

HRESULT CUI_Manager::SetUp_UILayer()
{
	g_pManagement->Add_GameObject_ToLayer(L"GameObject_QuickSlot", SCENE_STAGE, L"Layer_QuickSlot");
	g_pManagement->Add_GameObject_ToLayer(L"GameObject_ExpendablesInven", SCENE_STAGE, L"Layer_ExpendablesInven");
	g_pManagement->Add_GameObject_ToLayer(L"GameObject_MaterialInven", SCENE_STAGE, L"Layer_MaterialInven");
	g_pManagement->Add_GameObject_ToLayer(L"GameObject_WeaponInven", SCENE_STAGE, L"Layer_WeaponInven");
	g_pManagement->Add_GameObject_ToLayer(L"GameObject_ArmorInven", SCENE_STAGE, L"Layer_WeaponInven");

	return NOERROR;
}

_int CUI_Manager::Update_UI()
{
	

	return 0;
}

void CUI_Manager::Free()
{
}



