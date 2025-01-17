#pragma once

#include "BT_Task_Node.h"

BEGIN(Engine)

class CTransform;
class ENGINE_DLL CBT_RotationDir final : public CBT_Task_Node
{
public:
	typedef struct tagInitInfo
	{
		tagInitInfo(char* _pNodeName, CTransform* pThis_Transform, _tchar* _pTarget_Key, _double _TurnTime)
			: pTransform(pThis_Transform), dTurnTime(_TurnTime)
		{ strcpy_s<256>(Target_NodeName, _pNodeName); 
		lstrcpy(Target_Key, _pTarget_Key); }

		CTransform*	pTransform = nullptr;
		char		Target_NodeName[256] = { 0, };
		_tchar		Target_Key[256] = { 0, };
		_double		dTurnTime = 0;
	} INFO;

protected:
	explicit CBT_RotationDir();
	explicit CBT_RotationDir(const CBT_RotationDir& rhs);
	virtual ~CBT_RotationDir() = default;

public:
	virtual BT_NODE_STATE Update_Node(_double TimeDelta, vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, CBlackBoard* pBlackBoard, _bool bDebugging) override;

public:
	virtual void Start_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, _bool bDebugging);
	virtual BT_NODE_STATE End_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, BT_NODE_STATE eState, _bool bDebugging);

private:
	HRESULT Ready_Clone_Node(void* pInit_Struct);

	HRESULT Cal_Rotation_Angle(const _v3 vTarget_Pos);
	
private:
	CTransform*	m_pTransform = nullptr;
	_tchar		m_Target_Key[256] = { 0, };
	_double		m_dTurnTime = 0;

	_double		m_dDestRadian = 0;
	_double		m_dCurRadian = 0;
	_bool		m_bTurnLeft = false;
	_double		m_dDestRadian_Per_TurnTime = 0;

public:
	static CBT_RotationDir* Create_Prototype();
	virtual CBT_Node* Clone(void* pInit_Struct) override;

	virtual void Free();
};

END