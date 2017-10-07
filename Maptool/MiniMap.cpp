// MiniMap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Maptool.h"
#include "MiniMap.h"

#include "Define.h"
#include "Device.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "MapToolView.h"

// CMiniMap

IMPLEMENT_DYNCREATE(CMiniMap, CView)

CMiniMap::CMiniMap()
{

}

CMiniMap::~CMiniMap()
{
}

BEGIN_MESSAGE_MAP(CMiniMap, CView)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMiniMap 그리기입니다.

void CMiniMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	
	D3DXMATRIX	matWorld;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matTrans;
	
	/* 타일 20개 */
	//float		fScaleX = 0.66f;
	//float		fScaleY = 0.48f;

	/* 타일 30개 */
	float		fScaleX = 0.44f;
	float		fScaleY = 0.32f;

	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 1.f);

	GET_SINGLE(CDevice)->Render_Begin();

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	/* 오브젝트 렌더링 */
	vector<TILE*>* pvecTile = &pMainFrm->m_pMainView->m_vecTile;
	vector<OBJECT*>* pvecObj = &pMainFrm->m_pMainView->m_vecObj;
	vector<SYSTEM*>* pvecSys = &pMainFrm->m_pMainView->m_vecSys;
	vector<MONSTER*>* pvecMon = &pMainFrm->m_pMainView->m_vecMon;
	vector<NPC*>* pvecNPC = &pMainFrm->m_pMainView->m_vecNPC;

	for(int y = 0 ; y < TILECNTY; ++y)
	{
		for(int x = 0 ; x < TILECNTX; ++x)
		{
			int iIndex = y * TILECNTX + x;	

			if(iIndex >= TILECNTX * TILECNTY || iIndex < 0)
				continue;
			
			const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Tile");
			if(pTexInfo == NULL)
				continue;

						
			/* 타일 그리기 */
			for(int k = 0 ; k <= (*pvecTile)[iIndex]->vTilePos.z ; ++k)
			{
				D3DXMatrixTranslation(&matWorld,(*pvecTile)[iIndex]->vTilePos.x * fScaleX,
					((*pvecTile)[iIndex]->vTilePos.y - 16 * k) * fScaleY, 0.f);
				
				matWorld = matScale * matWorld;

				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&pMainFrm->m_pMainView->GetTileDraw(iIndex),&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));
				
				D3DXMatrixTranslation(&matWorld,(*pvecTile)[iIndex]->vRootPos.x * fScaleX,
					((*pvecTile)[iIndex]->vRootPos.y - 16 * k) * fScaleY, 0.f);
								
				matWorld = matScale * matWorld;

				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&pMainFrm->m_pMainView->GetRootDraw(iIndex),&D3DXVECTOR3(TILERTSIZEX / 2.f, TILERTSIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));
			}

			/* 오브젝트 그리기 */
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Tile");
			if(pTexInfo == NULL)
				continue;

			for(vector<OBJECT*>::iterator iterObj = (*pvecObj).begin() ; iterObj != (*pvecObj).end() ; ++iterObj)
			{
				if((*iterObj)->vObjPos.x == (*pvecTile)[iIndex]->vTilePos.x &&
					(*iterObj)->vObjPos.y == (*pvecTile)[iIndex]->vTilePos.y)
				{
					D3DXMatrixTranslation(&matWorld,(*iterObj)->vObjPos.x * fScaleX,
						((*iterObj)->vObjPos.y - 16 * (*pvecTile)[iIndex]->vTilePos.z) * fScaleY, 0.f);
					
					matWorld = matScale * matWorld;

					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &pMainFrm->m_pMainView->GetObjDraw((*iterObj)->byDrawId), 
						&D3DXVECTOR3((pMainFrm->m_pMainView->GetObjDraw((*iterObj)->byDrawId).right - pMainFrm->m_pMainView->GetObjDraw((*iterObj)->byDrawId).left) / 2.f, 
						(pMainFrm->m_pMainView->GetObjDraw((*iterObj)->byDrawId).bottom - pMainFrm->m_pMainView->GetObjDraw((*iterObj)->byDrawId).top) - TILESIZEY / 2.f, 0.f),
						NULL,D3DCOLOR_ARGB(255,255,255,255));
				}
			}
			/* 몬스터 그리기 */
			for(vector<MONSTER*>::iterator iterMon = (*pvecMon).begin() ; iterMon != (*pvecMon).end() ; ++iterMon)
			{
				if((*iterMon)->tObjInfo.vPos.x == (*pvecTile)[iIndex]->vTilePos.x &&
					(*iterMon)->tObjInfo.vPos.y == (*pvecTile)[iIndex]->vTilePos.y)
				{	
					RECT rcMon = { 0, 0, 100, 100};
					RECT rcBoss = { 100, 0, 200, 100};

					pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Mon_MiniMap");
					if(pTexInfo == NULL)
						continue;

					switch((*iterMon)->eClass)
					{
					case PHYSICAL_CLASS:
					case MAGICAL_CLASS:
						D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x * fScaleX,
							((*iterMon)->tObjInfo.vPos.y - 16 * (*pvecTile)[iIndex]->vTilePos.z) * fScaleY, 0.f);

						GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
						GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
							&rcMon, &(*iterMon)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
						break;
					case BOSS_CLASS:
						D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x * fScaleX,
							((*iterMon)->tObjInfo.vPos.y - 16 * (*pvecTile)[iIndex]->vTilePos.z) * fScaleY, 0.f);
					
						(*iterMon)->tObjInfo.matWorld = matScale * (*iterMon)->tObjInfo.matWorld;

						GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
						GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
							&rcBoss, &(*iterMon)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
						break;
					}
				}
			}
			/* NPC 그리기 */
			for(vector<NPC*>::iterator iterNPC = (*pvecNPC).begin() ; iterNPC != (*pvecNPC).end() ; ++iterNPC)
			{
				if((*iterNPC)->tObjInfo.vPos.x == (*pvecTile)[iIndex]->vTilePos.x &&
					(*iterNPC)->tObjInfo.vPos.y == (*pvecTile)[iIndex]->vTilePos.y)
				{
					RECT rcNPC = { 0, 0, 100, 100};
					pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"NPC_MiniMap");
					if(pTexInfo == NULL)
						continue;
					D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x * fScaleX,
						((*iterNPC)->tObjInfo.vPos.y - 16 * (*pvecTile)[iIndex]->vTilePos.z) * fScaleY, 0.f);
					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
						&rcNPC,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				}
			}

			/* 워프 그리기 */
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Warp");
			if(pTexInfo == NULL)
				continue;

			for(vector<SYSTEM*>::iterator iterSys = (*pvecSys).begin() ; iterSys != (*pvecSys).end() ; ++iterSys)
			{
				if((*iterSys)->vSysPos.x == (*pvecTile)[iIndex]->vTilePos.x &&
					(*iterSys)->vSysPos.y == (*pvecTile)[iIndex]->vTilePos.y)
				{
					/* 첫 귀환장소만 출력 안함 */
					if((*iterSys)->byDrawId != 7)
					{
						D3DXMatrixTranslation(&matWorld, (*iterSys)->vSysPos.x * fScaleX,
							((*iterSys)->vSysPos.y - 16 * (*pvecTile)[iIndex]->vTilePos.z) * fScaleY, 0.f);
						GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
						GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &pMainFrm->m_pMainView->GetWarpDraw((*iterSys)->byDrawId), 
							&D3DXVECTOR3((pMainFrm->m_pMainView->GetWarpDraw((*iterSys)->byDrawId).right - pMainFrm->m_pMainView->GetWarpDraw((*iterSys)->byDrawId).left) / 2.f, 
							(pMainFrm->m_pMainView->GetWarpDraw((*iterSys)->byDrawId).bottom - pMainFrm->m_pMainView->GetWarpDraw((*iterSys)->byDrawId).top), 0.f),
							NULL,D3DCOLOR_ARGB(255,255,255,255));
					}
				}
			}
			//wsprintf(szTmp,L"%d",iIndex);
			//GET_SINGLE(CDevice)->GetFont()->DrawTextW(GET_SINGLE(CDevice)->GetSprite(),
			//	szTmp,lstrlen(szTmp),&rcFont,DT_NOCLIP,D3DCOLOR_ARGB(255,0,0,0));
		}
	}
	
	/* 오브젝트 렌더링 */
	GET_SINGLE(CDevice)->Render_End(m_hWnd);
}


// CMiniMap 진단입니다.

#ifdef _DEBUG
void CMiniMap::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniMap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniMap 메시지 처리기입니다.


void CMiniMap::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->m_pMainView->m_pMiniMap = this;
}