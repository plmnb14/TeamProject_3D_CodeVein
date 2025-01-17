#pragma  once

#include "BT_Node.h"

/*
BehaviorTree의 시작점입니다.
service나 decorator를 Root에 할당할 수 없습니다.

Composite 이나 Task만 child에 할당 가능합니다.
*/

BEGIN(Engine)

class CBT_Decorator_Node;
class CBT_Composite_Node;
class CBT_Task_Node;
class ENGINE_DLL CBT_Root final : public CBT_Node
{
protected:
	explicit CBT_Root();
	virtual ~CBT_Root() = default;

public:
	HRESULT Set_Child(CBT_Node* pNode);

public:
	virtual BT_NODE_STATE Update_Node(_double TimeDelta, vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, CBlackBoard* pBlackBoard,  _bool bDebugging) override;

protected:
	virtual void Start_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, _bool bDebugging);
	virtual BT_NODE_STATE End_Node(vector<CBT_Node*>* pNodeStack, list<vector<CBT_Node*>*>* plistSubNodeStack, BT_NODE_STATE eState, _bool bDebugging);

private:
	CBT_Node*		m_pChildNode = nullptr;

public:
	static CBT_Root* Create();

	virtual CBT_Node* Clone(void* pInit_Struct) override { return nullptr; }

	virtual void Free();
};

END