#include "StdAfx.h"
#include "AStar.h"
#include "ObjMgr.h"

CAStar::CAStar(void)
{
}


CAStar::~CAStar(void)
{
	Release();
}

void CAStar::AStarStart(const int& iStartIdx, const int& iGoalIdx)
{
	if(iStartIdx == iGoalIdx)
		return;

	const vector<TILE*>* pVecTile = GET_SINGLE(CObjMgr)->GetTileInfo();
	const vector<OBJECT*>* pVecObj = GET_SINGLE(CObjMgr)->GetObjInfo();

	if(pVecTile == NULL)
		return;

	/* 타일이 없을 경우 */
	if((*pVecTile)[iGoalIdx]->vTilePos.z < 0)
		return;

	/* 오브젝트가 있을 경우 */
	for(size_t i = 0 ; i < pVecObj->size() ; ++i)
	{
		if((*pVecTile)[iGoalIdx]->vTilePos.x == (*pVecObj)[i]->vObjPos.x
			&& (*pVecTile)[iGoalIdx]->vTilePos.y == (*pVecObj)[i]->vObjPos.y)
			return ; 
	}

	Release();

	m_iStartIdx = iStartIdx;
	m_iGoalIdx = iGoalIdx;

	MakeRoute();
}

void CAStar::MakeRoute()
{
	NODE* pParent = new NODE;
	pParent->iIndex = m_iStartIdx;
	pParent->pParent = NULL;
	pParent->fCost = 0;

	m_CloseList.push_back(pParent);

	const vector<TILE*>* pVecTile = GET_SINGLE(CObjMgr)->GetTileInfo();
	if(pVecTile == NULL)
		return;

	NODE*	pNode = NULL;
	int     iIndex = 0;

	while (true)
	{
		//오른쪽 위
		iIndex = pParent->iIndex - (TILECNTX - (pParent->iIndex/TILECNTX) % 2);

		float temp = (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z;

		if( pParent->iIndex >= TILECNTX
			&& pParent->iIndex % (TILECNTX * 2) != TILECNTX * 2 -1
			&& -1 <= (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z
 			&& (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z <= 1
			&& (*pVecTile)[iIndex]->vTilePos.z >= 0
			&& CheckList(iIndex))
		{
			pNode = MakeNode(iIndex,pParent,pVecTile);
			m_OpenList.push_back(pNode);
		}

		//오.아
		iIndex = pParent->iIndex + (TILECNTX  + ((pParent->iIndex/ TILECNTX) % 2));

		if( pParent->iIndex < TILECNTX * TILECNTY - TILECNTX
			&& pParent->iIndex % (TILECNTX * 2) != TILECNTX *2 -1
			&& -1 <= (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z
 			&& (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z <= 1
			&& (*pVecTile)[iIndex]->vTilePos.z >= 0
			&& CheckList(iIndex))
		{
			pNode = MakeNode(iIndex,pParent,pVecTile);
			m_OpenList.push_back(pNode);
		}

		//왼쪽 아래
		iIndex = pParent->iIndex + (TILECNTX  - 1 + (pParent->iIndex/ TILECNTX) % 2);

		if( pParent->iIndex < TILECNTX * TILECNTY - TILECNTX
			&& pParent->iIndex % (TILECNTX * 2) != 0
			&& -1 <= (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z
 			&& (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z <= 1
			&& (*pVecTile)[iIndex]->vTilePos.z >= 0
			&& CheckList(iIndex))
		{
			pNode = MakeNode(iIndex,pParent,pVecTile);
			m_OpenList.push_back(pNode);
		}

		//왼.위
		iIndex = pParent->iIndex - (TILECNTX + 1 - (pParent->iIndex / TILECNTX) % 2);
		if( pParent->iIndex >= TILECNTX
			&& pParent->iIndex % (TILECNTX * 2) != 0
			&& -1 <= (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z
 			&& (*pVecTile)[pParent->iIndex]->vTilePos.z - (*pVecTile)[iIndex]->vTilePos.z <= 1
			&& (*pVecTile)[iIndex]->vTilePos.z >= 0
			&& CheckList(iIndex))
		{
			pNode = MakeNode(iIndex,pParent,pVecTile);
			m_OpenList.push_back(pNode);
		}

		if(m_OpenList.empty())
			return;

		m_OpenList.sort(Compare);

		list<NODE*>::iterator iter = m_OpenList.begin();
		pParent = *iter;
		
		m_CloseList.push_back(*iter);
		m_OpenList.erase(iter);

		if(pParent->iIndex == m_iGoalIdx)
		{
			while(true)
			{
				m_BestList.push_back(pParent->iIndex);
				pParent = pParent->pParent;
				if(pParent->iIndex == m_iStartIdx)
					break;
			}
			m_BestList.reverse();
			break;
		}
	}
}

bool CAStar::CheckList(const int& iIndex)
{
	for (list<NODE*>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	for (list<NODE*>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	return true;
}

NODE* CAStar::MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pvecTile)
{
	NODE*  pNode = new NODE;
	pNode->iIndex = iIndex;
	pNode->pParent = pParent;

	//부모 노드까지 거리
	D3DXVECTOR3 vDir = (*pvecTile)[iIndex]->vTilePos - (*pvecTile)[pParent->iIndex]->vTilePos;
	float		fPCost = D3DXVec3Length(&vDir);

	//도착 노드까지 거리
	vDir = (*pvecTile)[iIndex]->vTilePos - (*pvecTile)[m_iGoalIdx]->vTilePos;
	float		fGCost = D3DXVec3Length(&vDir);

	pNode->fCost = fPCost + fGCost;

	return pNode;
}

void CAStar::Release()
{
	for(list<NODE*>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter) 
	{
		SAFE_DELETE(*iter);
	}
	m_OpenList.clear();

	for(list<NODE*>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter) 
	{
		SAFE_DELETE(*iter);
	}
	m_CloseList.clear();
	m_BestList.clear();
}