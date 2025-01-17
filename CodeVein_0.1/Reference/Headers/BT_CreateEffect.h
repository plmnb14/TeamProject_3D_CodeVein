#pragma once

#include "BT_Service_Node.h"

BEGIN(Engine)

class ENGINE_DLL CBT_CreateEffect final : public CBT_Service_Node
{
public:
	enum Mode { One, Particle};

	typedef struct tagInitInfo
	{
		tagInitInfo(char* pNodeName, _tchar* _Effect_Tag, _v3 _Effect_Create_Pos, _float _Effect_Life_Time, _uint _MaxCount_Of_Execution, _double dCreateTime, _double dOffset, CBT_Service_Node::Mode _eMode, CBT_CreateEffect::Mode _eEffect_Mode)
			: Effect_Create_Pos(_Effect_Create_Pos), Effect_Life_Time(_Effect_Life_Time), Target_dCreateTime(dCreateTime), Target_dOffset(dOffset), MaxCount_Of_Execution(_MaxCount_Of_Execution), eEffect_Mode(_eEffect_Mode)
		{ strcpy_s<256>(Target_NodeName, pNodeName);
		lstrcpy(Effect_Tag, _Effect_Tag);}

		char					Target_NodeName[256] = {0,};
		_tchar					Effect_Tag[256] = { 0, };
		_v3						Effect_Create_Pos = _v3(0.f, 0.f, 0.f);
		_float					Effect_Life_Time = 0.f;
		_double					Target_dCreateTime = 0;
		_double					Target_dOffset = 0;
		_uint					MaxCount_Of_Execution = 0;
		CBT_Service_Node::Mode	eMode = CBT_Service_Node::Infinite;
		CBT_CreateEffect::Mode	eEffect_Mode = CBT_CreateEffect::One;
	}INFO;

protected:
	explicit CBT_CreateEffect();
	explicit CBT_CreateEffect(const CBT_CreateEffect& rhs);
	virtual ~CBT_CreateEffect() = default;

public:
	virtual BT_NODE_STATE Update_Node(_double TimeDelta, vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, CBlackBoard* pBlackBoard, _bool bDebugging) override;

public:
	virtual void Start_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, _bool bDebugging);
	virtual BT_NODE_STATE End_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, BT_NODE_STATE eState, _bool bDebugging);

private:
	HRESULT Ready_Clone_Node(void* pInit_Struct);

	// dMaxTime = m_dWaitingTime +- m_dOffset
	_double		m_dMaxTime = 0;

private:
	_tchar					m_pEffect_Tag[256] = { 0, };
	_v3						m_vEffect_Pos = _v3(0.f, 0.f, 0.f);
	_float					m_fEffect_lifeTime = 0.f;
	CBT_CreateEffect::Mode	m_eEffectMode = CBT_CreateEffect::One;

	_double					m_dCurTime = 0;
	_double					m_dCreateTime = 0;
	_double					m_dOffset = 0;

	_tchar					m_pTargetKey[256] = { 0, };

public:
	static CBT_CreateEffect* Create_Prototype();
	virtual CBT_CreateEffect* Clone(void* pInit_Struct) override;

	virtual void Free();
};

END