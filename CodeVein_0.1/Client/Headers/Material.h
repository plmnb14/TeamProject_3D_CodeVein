#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Client)

class CMaterial final : public CGameObject
{
public:
	enum MATERIAL_TYPE
	{
		MATERIAL_1,
		MATERIAL_2,
		MATERIAL_3,
		MATERIAL_4,
		MATERIAL_END
	};

private:
	explicit CMaterial(_Device pDevice);
	explicit CMaterial(const CMaterial& rhs);
	virtual ~CMaterial() = default;

public:
	MATERIAL_TYPE Get_Type() { return m_eType; }

public:
	void Set_Type(MATERIAL_TYPE eType) { m_eType = eType; }

public:
	virtual HRESULT Ready_GameObject_Prototype();
	virtual HRESULT Ready_GameObject(void* pArg);
	virtual _int	Update_GameObject(_double TimeDelta);

private:
	MATERIAL_TYPE m_eType;

public:
	static CMaterial*		Create(_Device pGraphic_Device);
	virtual CGameObject*	Clone_GameObject(void* pArg);
	virtual void			Free();
};

END

