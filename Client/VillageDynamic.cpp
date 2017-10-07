#include "StdAfx.h"
#include "VillageDynamic.h"

#include "Astar.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

CVillageDynamic::CVillageDynamic(void)
{
}

CVillageDynamic::CVillageDynamic(const OBJ_INFO& _Info)
	:CObj(_Info), m_fAngle(0.f)
{
}


CVillageDynamic::~CVillageDynamic(void)
{
}

void CVillageDynamic::Chase_Move(const OBJ_INFO& DestInfo)
{
	m_Info.vDir = DestInfo.vPos - m_Info.vPos;
	float fDistance = D3DXVec3LengthSq(&m_Info.vDir);

	if(fDistance > 10)
	{
		D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
		m_Info.vPos += m_Info.vDir * 10.f;
	}
}

void CVillageDynamic::SetDirect( const OBJ_INFO& DestInfo )
{
	D3DXVECTOR3 vDirection = DestInfo.vPos - m_Info.vPos;
	D3DXVec3Normalize(&vDirection,&vDirection);
	D3DXVec3Normalize(&m_Info.vLook,&m_Info.vLook);

	m_fAngle = acosf(D3DXVec3Dot(&vDirection,&m_Info.vLook));

	if(DestInfo.vPos.y < m_Info.vPos.y)
	{
		m_fAngle = 2*D3DX_PI - m_fAngle;
	}
}

void CVillageDynamic::AStar_Start(const D3DXVECTOR3& vDestPos,D3DXVECTOR3& vSourPos )
{
	int iStartIdx = GetTileIndex(vDestPos);
	if(iStartIdx < 0)
		return;

	int iGoalIdx = GetTileIndex(vSourPos);
	if(iGoalIdx < 0)
		return;

	GET_SINGLE(CAStar)->AStarStart(iStartIdx,iGoalIdx);
}

void CVillageDynamic::AStar_Move( void )
{
	list<int>* pBestList = GET_SINGLE(CAStar)->GetBestList();
	if(pBestList->empty())
		return;

	const vector<TILE*>* pVecTile = GET_SINGLE(CObjMgr)->GetTileInfo();
	int iDestIdx = pBestList->front();
	
	m_Info.vDir = (*pVecTile)[iDestIdx]->vTilePos - m_Info.vPos;
	
	 float fDistance = D3DXVec3Length(&m_Info.vDir);
	 D3DXVec3Normalize(&m_Info.vDir,&m_Info.vDir);
	
	 m_Info.vPos += m_Info.vDir * 200.f * GET_SINGLE(CTimeMgr)->GetTime();

	 if(fDistance < 5.f)
		 pBestList->pop_front();
}
