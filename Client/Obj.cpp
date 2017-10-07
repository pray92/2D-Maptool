#include "StdAfx.h"
#include "Obj.h"

#include "TimeMgr.h"
#include "ObjMgr.h"

D3DXVECTOR3 CObj::m_vScroll( 0.f, 0.f, 0.f);
D3DXVECTOR3 CObj::m_vOffset(WINSIZEX / 2.f, WINSIZEY / 2.f, 0.f);

CObj::CObj(void)
{
}


CObj::~CObj(void)
{
}

CObj::CObj(const OBJ_INFO& _Info)
	:m_Info(_Info),m_SortID(SORT_ID_NULL)
{
}


void CObj::Multi_Frame_Move(const float& _fCnt, const float& _fMax)
{
	m_fFrame += _fCnt * GET_SINGLE(CTimeMgr)->GetTime();
	if(m_fFrame > _fMax)
	{
		m_fFrame = 0.f;
	}
}

void CObj::Single_Frame_Move(const float& _fCnt)
{
	m_tFrame.fStart += _fCnt * GET_SINGLE(CTimeMgr)->GetTime();
	if(m_tFrame.fStart > m_tFrame.fLast)
	{
		m_tFrame.fStart = 0.f;
	}
}

void CObj::SetScene(const float& _fLast, const int& _iScene)
{
	if(m_tFrame.iScene != _iScene)
		m_tFrame.fStart = 0;

	m_tFrame.fLast =  _fLast;
	m_tFrame.iScene = _iScene;
}

OBJ_INFO CObj::SetMouseInfo()
{
	POINT	ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd,&ptMouse);

	OBJ_INFO	MouseInfo;
	ZeroMemory(&MouseInfo,sizeof(OBJ_INFO));

	MouseInfo.vPos = D3DXVECTOR3(float(ptMouse.x),float(ptMouse.y),0.f);
	
	return MouseInfo;
}

int CObj::GetTileIndex(const D3DXVECTOR3& vPos )
{
	const vector<TILE*>* pVecTile = GET_SINGLE(CObjMgr)->GetTileInfo();
	list<int> listInt;

	for (size_t i =0; i < pVecTile->size(); ++i)
	{
		//vPos.y += (*pVecTile)[i]->vTilePos.z * 16;
		if(CollsionMouseToTile(vPos,(*pVecTile)[i]))
		{
			listInt.push_back(i);
			//return i;
		}
	}
	
	if(listInt.empty())
		return -1;
	else
	{
		listInt.sort(greater<int>());
		return *listInt.begin();
	}
}

bool CObj::CollsionMouseToTile(D3DXVECTOR3 vMousePoint,const TILE* pTileInfo)
{
	float fGrad = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	D3DXVECTOR2	vPoint[4];

	vPoint[0] = D3DXVECTOR2(pTileInfo->vTilePos.x - TILESIZEX/2.f + m_vScroll.x, pTileInfo->vTilePos.y + m_vScroll.y - 16 * pTileInfo->vTilePos.z);
	vPoint[1] = D3DXVECTOR2(pTileInfo->vTilePos.x + m_vScroll.x, pTileInfo->vTilePos.y + TILESIZEY/2.f + m_vScroll.y - 16 * pTileInfo->vTilePos.z);
	vPoint[2] = D3DXVECTOR2(pTileInfo->vTilePos.x + TILESIZEX/2.f + m_vScroll.x, pTileInfo->vTilePos.y + m_vScroll.y - 16 * pTileInfo->vTilePos.z);
	vPoint[3] = D3DXVECTOR2(pTileInfo->vTilePos.x + m_vScroll.x, pTileInfo->vTilePos.y - TILESIZEY/2 + m_vScroll.y - 16 * pTileInfo->vTilePos.z);


	float fB[4];
	fB[0] = vPoint[0].y - fGrad * vPoint[0].x;
	fB[1] = vPoint[1].y + fGrad * vPoint[1].x;
	fB[2] = vPoint[2].y - fGrad * vPoint[2].x;
	fB[3] = vPoint[3].y + fGrad * vPoint[3].x;


	if(vMousePoint.y - 16 * pTileInfo->vTilePos.z - fGrad * vMousePoint.x - fB[0] <= 0 &&
		vMousePoint.y - 16 * pTileInfo->vTilePos.z +fGrad * vMousePoint.x - fB[1] <= 0 &&
		vMousePoint.y - 16 * pTileInfo->vTilePos.z - fGrad * vMousePoint.x - fB[2] > 0 &&
		vMousePoint.y - 16 * pTileInfo->vTilePos.z +fGrad * vMousePoint.x - fB[3] > 0)
	{
		return true;
	}

	return false;

}