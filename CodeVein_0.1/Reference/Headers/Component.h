#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CComponent abstract : public CBase
{	
protected:
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent() = default;

public:
	virtual _int Update_Component();

public:
	virtual HRESULT Ready_Component_Prototype();
	virtual HRESULT Ready_Component(void* pArg);
protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Dev = nullptr;
	_bool					m_bisClone = false;
public:
	virtual CComponent* Clone_Component(void* pArg) = 0;
	virtual void Free();
};

END