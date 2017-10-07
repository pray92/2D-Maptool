#pragma once

class CAStar
{
public:
	DECLARE_SINGLETON(CAStar);
private:
	list<NODE*>		m_OpenList;			//조사해야 될 노드
	list<NODE*>		m_CloseList;		//조사완료된 노드
	list<int>		m_BestList;
public:
	list<int>* GetBestList() { return &m_BestList; };
public:
	int m_iStartIdx;
	int m_iGoalIdx;

	static bool Compare(NODE* pDestNode, NODE* pSourceNode)
	{
		return pDestNode->fCost < pSourceNode->fCost;
	}
public:
	void AStarStart(const int & iStartIdx,
		const int& iGoalIdx);
	void MakeRoute();
	bool CheckList(const int& iIndex);
	NODE* MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pvecTile);
	void Release();
public:
	CAStar(void);
	~CAStar(void);
};

