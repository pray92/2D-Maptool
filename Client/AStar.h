#pragma once

class CAStar
{
public:
	DECLARE_SINGLETON(CAStar);
private:
	list<NODE*>		m_OpenList;			//�����ؾ� �� ���
	list<NODE*>		m_CloseList;		//����Ϸ�� ���
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

