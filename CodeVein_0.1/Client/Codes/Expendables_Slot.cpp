#include "stdafx.h"
#include "..\Headers\Expendables_Slot.h"


// 0 ~ 아이템, End-> 없음

CExpendables_Slot::CExpendables_Slot(_Device pDevice)
	: CUI(pDevice)
{
}

CExpendables_Slot::CExpendables_Slot(const CExpendables_Slot & rhs)
	: CUI(rhs)
{
}

void CExpendables_Slot::Set_Select(_bool bIsSelect)
{
	m_bIsSelect = bIsSelect;
}

HRESULT CExpendables_Slot::Ready_GameObject_Prototype()
{
	CUI::Ready_GameObject_Prototype();

	return NOERROR;
}

HRESULT CExpendables_Slot::Ready_GameObject(void * pArg)
{
	if (FAILED(Add_Component()))
		return DEAD_OBJ;
	CUI::Ready_GameObject(pArg);

	if (FAILED(SetUp_Default()))
		return E_FAIL;
	
	return NOERROR;
}

_int CExpendables_Slot::Update_GameObject(_double TimeDelta)
{
	CUI::Update_GameObject(TimeDelta);

	if (m_pSelectUI)
	{
		m_pSelectUI->Set_Active(m_bIsActive);
		m_pSelectUI->Set_UI_Pos(m_fPosX, m_fPosY);
		m_pSelectUI->Set_UI_Size(m_fSizeX, m_fSizeY);
		m_pSelectUI->Set_ViewZ(m_fViewZ - 0.1f);
	}

	m_pRendererCom->Add_RenderList(RENDER_UI, this);

	D3DXMatrixOrthoLH(&m_matProj, WINCX, WINCY, 0.f, 1.f);

	if (m_vecExpendables.size() > 0)
		m_iIndex = m_vecExpendables.front()->Get_Type();
	else
		m_iIndex = CExpendables::EXPEND_END;

	if (m_vecExpendables.size() > 0)
		m_pSelectUI->Set_Select(m_bIsSelect);
	else
		m_pSelectUI->Set_Select(false);
	return NO_EVENT;
}

_int CExpendables_Slot::Late_Update_GameObject(_double TimeDelta)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);

	m_matWorld._11 = m_fSizeX;
	m_matWorld._22 = m_fSizeY;
	m_matWorld._33 = 1.f;
	m_matWorld._41 = m_fPosX - WINCX * 0.5f;
	m_matWorld._42 = -m_fPosY + WINCY * 0.5f;

	return NO_EVENT;
}

HRESULT CExpendables_Slot::Render_GameObject()
{
	if (!m_bIsActive)
		return NOERROR;

	if (nullptr == m_pShaderCom ||
		nullptr == m_pBufferCom)
		return E_FAIL;


	g_pManagement->Set_Transform(D3DTS_WORLD, m_matWorld);

	m_matOldView = g_pManagement->Get_Transform(D3DTS_VIEW);
	m_matOldProj = g_pManagement->Get_Transform(D3DTS_PROJECTION);

	g_pManagement->Set_Transform(D3DTS_VIEW, m_matView);
	g_pManagement->Set_Transform(D3DTS_PROJECTION, m_matProj);


	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	m_pShaderCom->Begin_Shader();

	m_pShaderCom->Begin_Pass(0);

	m_pBufferCom->Render_VIBuffer();

	m_pShaderCom->End_Pass();

	m_pShaderCom->End_Shader();


	g_pManagement->Set_Transform(D3DTS_VIEW, m_matOldView);
	g_pManagement->Set_Transform(D3DTS_PROJECTION, m_matOldProj);

	return NOERROR;
}

void CExpendables_Slot::Input_Item(CExpendables * pExpendables)
{
	if (nullptr == pExpendables)
		return;

	m_vecExpendables.push_back(pExpendables);
}

_bool CExpendables_Slot::Pt_InRect()
{
	return g_pInput_Device->MousePt_InRect(m_fPosX, m_fPosY, m_fSizeX, m_fSizeY, g_hWnd);
}

_uint CExpendables_Slot::Get_Size()
{
	return _uint(m_vecExpendables.size());
}

_uint CExpendables_Slot::Get_Type()
{
	if (m_vecExpendables.size() == 0)
		return CExpendables::EXPEND_END;
	return _uint(m_vecExpendables.front()->Get_Type());
}

void CExpendables_Slot::Delete_Item()
{
	if (m_vecExpendables.size() == 0)
		return;
	m_vecExpendables.pop_back();
}

void CExpendables_Slot::Delete_Items()
{
	for (_uint i = 0; i < m_vecExpendables.size(); ++i)
		m_vecExpendables.pop_back();
}



HRESULT CExpendables_Slot::Add_Component()
{
	// For.Com_Transform
	if (FAILED(CGameObject::Add_Component(SCENE_STATIC, L"Transform", L"Com_Transform", (CComponent**)&m_pTransformCom)))
		return E_FAIL;

	// For.Com_Renderer
	if (FAILED(CGameObject::Add_Component(SCENE_STATIC, L"Renderer", L"Com_Renderer", (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	// For.Com_Texture
	if (FAILED(CGameObject::Add_Component(SCENE_STATIC, L"Tex_Expendables", L"Com_Texture", (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	// For.Com_Shader
	if (FAILED(CGameObject::Add_Component(SCENE_STATIC, L"Shader_UI", L"Com_Shader", (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	// for.Com_VIBuffer
	if (FAILED(CGameObject::Add_Component(SCENE_STATIC, L"VIBuffer_Rect", L"Com_VIBuffer", (CComponent**)&m_pBufferCom)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CExpendables_Slot::SetUp_ConstantTable()
{
	if (nullptr == m_pShaderCom)
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_Value("g_matWorld", &m_matWorld, sizeof(_mat))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_Value("g_matView", &m_matView, sizeof(_mat))))

		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_Value("g_matProj", &m_matProj, sizeof(_mat))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_OnShader("g_DiffuseTexture", m_pShaderCom, m_iIndex)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CExpendables_Slot::SetUp_Default()
{
	CUI::UI_DESC* pDesc = new CUI::UI_DESC;
	pDesc->fPosX = m_fPosX;
	pDesc->fPosY = m_fPosY;
	pDesc->fSizeX = m_fSizeX;
	pDesc->fPosY = m_fSizeY;
	if (FAILED(g_pManagement->Add_GameObject_ToLayer(L"GameObject_SelectUI", SCENE_STAGE, L"Layer_SelectUI", pDesc)))
		return E_FAIL;
	m_pSelectUI = static_cast<CSelect_UI*>(g_pManagement->Get_GameObjectBack(L"Layer_SelectUI", SCENE_STAGE));
	return NOERROR;
}



CExpendables_Slot * CExpendables_Slot::Create(_Device pGraphic_Device)
{
	CExpendables_Slot* pInstance = new CExpendables_Slot(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("CExpendables_Slot Creating Fail");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CExpendables_Slot::Clone_GameObject(void * pArg)
{
	CExpendables_Slot* pInstance = new CExpendables_Slot(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("CExpendables_Slot Cloned Fail");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CExpendables_Slot::Free()
{
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pBufferCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pRendererCom);

	CUI::Free();
}
