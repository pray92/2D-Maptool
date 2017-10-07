
// MaptoolView.cpp : CMaptoolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Maptool.h"
#endif

#include "MaptoolDoc.h"
#include "MaptoolView.h"

#include "Define.h"
#include "Device.h"
#include "TextureMgr.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMaptoolView

IMPLEMENT_DYNCREATE(CMaptoolView, CScrollView)

BEGIN_MESSAGE_MAP(CMaptoolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMaptoolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMaptoolView 생성/소멸

CMaptoolView::CMaptoolView()
	:m_iSelectObjID(-1), m_iSelectTileID(-1), m_iSelectWarpID(-1), m_iSelectMonsterID(-1), m_iSelectNPCID(-1)
	, m_MonsterClass(MONSTER_CLASS_NULL), m_NPCClass(NPC_CLASS_NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMaptoolView::~CMaptoolView()
{
}

BOOL CMaptoolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// 타일 초기화 및 설정 함수
void CMaptoolView::InitTile()
{
	m_vecTile.reserve(TILECNTX * TILECNTY * 2);

	for (int y = 0; y < TILECNTY; ++y)
	{
		for (int x = 0; x < TILECNTX; ++x)
		{
			int iIndex = y * TILECNTX + x;

			TILE*	pTile = new TILE;
			/* 타일 초기화 */
			pTile->vTilePos = D3DXVECTOR3(x * TILESIZEX + (y % 2) * (TILESIZEX / 2.f), y * (TILESIZEY / 2.f), 0.f);
			pTile->vTileSize = D3DXVECTOR3((float)TILESIZEX, (float)TILESIZEY, 0.f);
			/* 타일 뿌리 초기화 */
			pTile->vRootPos = D3DXVECTOR3(pTile->vTilePos.x, y * (TILERTSIZEY / 2.f) /* 뿌리 위치 */ + 16.f, 0.f);
			pTile->vRootSize = D3DXVECTOR3((float)TILERTSIZEX, (float)TILERTSIZEY, 0.f);

			pTile->byDrawId =0;
			pTile->byOption =0;

			m_vecTile.push_back(pTile);
		}
	}

}

/* 오브젝트 초기화 */
void CMaptoolView::InitObj()
{
	m_vecObj.reserve(TILECNTX * TILECNTY * 2);
}

/* 워프 초기화 */
void CMaptoolView::InitSystem()
{
	m_vecSys.reserve(TILECNTX * TILECNTY * 2);
}

/* 몬스터 초기화 */
void CMaptoolView::InitMonster()
{
	m_vecMon.reserve(TILECNTX * TILECNTY * 2);
}

/* NPC 초기화 */
void CMaptoolView::InitNPC()
{
	m_vecNPC.reserve(TILECNTX * TILECNTY * 2);
}

bool CMaptoolView::CollisionMouseToTile(D3DXVECTOR3 vMousePoint,const TILE* pTileInfo)
{
	float fGrad = (TILESIZEY/2.f) / (TILESIZEX/2.f);

	D3DXVECTOR3	vPoint[4];

	vPoint[0] = D3DXVECTOR3(pTileInfo->vTilePos.x- TILESIZEX/2.f,pTileInfo->vTilePos.y, 0.f);
	vPoint[1] = D3DXVECTOR3(pTileInfo->vTilePos.x,pTileInfo->vTilePos.y + TILESIZEY/2.f, 0.f);
	vPoint[2] = D3DXVECTOR3(pTileInfo->vTilePos.x + TILESIZEX/2.f ,pTileInfo->vTilePos.y, 0.f);
	vPoint[3] = D3DXVECTOR3(pTileInfo->vTilePos.x ,pTileInfo->vTilePos.y - TILESIZEY/2, 0.f);


	float fB[4];
	fB[0] = vPoint[0].y - fGrad * vPoint[0].x;
	fB[1] = vPoint[1].y + fGrad * vPoint[1].x;
	fB[2] = vPoint[2].y - fGrad * vPoint[2].x;
	fB[3] = vPoint[3].y + fGrad * vPoint[3].x;


	if(vMousePoint.y - fGrad * vMousePoint.x - fB[0] <= 0 &&
		vMousePoint.y + fGrad * vMousePoint.x - fB[1] <= 0 &&
		vMousePoint.y - fGrad * vMousePoint.x - fB[2] > 0 &&
		vMousePoint.y + fGrad * vMousePoint.x - fB[3] > 0)
	{
		return true;
	}

	return false;
}

RECT CMaptoolView::GetTileDraw(int _iIndex)
{
	RECT rcTile = {};

	switch(m_vecTile[_iIndex]->byDrawId)
	{
	case 0:
		rcTile.left = 1;
		rcTile.top = 0;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 1:
		rcTile.left = 193;
		rcTile.top = 0;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 2:
		rcTile.left = 385;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = 0;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 3:
		rcTile.left = 449;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = 0;
		rcTile.bottom = TILESIZEY;
		break;
	case 4:
		rcTile.left = 385;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 5:
		rcTile.left = 449;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 6:
		rcTile.left = 385;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY * 2;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 7:
		rcTile.left = 449;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY * 2;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 8:
		rcTile.left = 385;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY * 3;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 9:
		rcTile.left = 449;
		rcTile.right = rcTile.left + TILESIZEX;
		rcTile.top = TILESIZEY * 3;
		rcTile.bottom = rcTile.top + TILESIZEY;
		break;
	case 10:
		rcTile.left = 897;
		rcTile.right = 958;
		rcTile.top = 224;
		rcTile.bottom = 255;
	}
	return rcTile;
}

RECT CMaptoolView::GetRootDraw(int _iIndex)
{
	RECT rcTile = {};

	/* 뿌리 */
	switch(m_vecTile[_iIndex]->byDrawId)
	{
	case 1:
		rcTile.left = 320;
		rcTile.top = 0;
		rcTile.right = rcTile.left + TILERTSIZEX;
		rcTile.bottom = rcTile.top + TILERTSIZEY;
		break;
	case 10:
		rcTile.left = 1152;
		rcTile.top = 0;
		rcTile.right = 1215;
		rcTile.bottom = 31;
		break;
	default:
		rcTile.left = 128;
		rcTile.top =  0;
		rcTile.right = rcTile.left + TILERTSIZEX;
		rcTile.bottom = rcTile.top + TILERTSIZEY;
		break;
	}

	return rcTile;
}

RECT CMaptoolView::GetObjDraw(int _iDrawID)
{
	RECT	rcTile = {};

	/* 오브젝트 크기 설정 */
	switch(_iDrawID)
	{
	case 1:
		rcTile.left = 128;
		rcTile.right = 191;
		rcTile.top = 130;
		rcTile.bottom = 171;
		break;
	case 2:
		rcTile.left = 128;
		rcTile.right = 191;
		rcTile.top = 178;
		rcTile.bottom = 219;
		break;
	case 3:
		rcTile.left = 128;
		rcTile.right = 191;
		rcTile.top = 220;
		rcTile.bottom = 267;
		break;
	case 4:
		rcTile.left = 128;
		rcTile.right = 191;
		rcTile.top = 268;
		rcTile.bottom = 331;
		break;
	case 5:
		rcTile.left = 193;
		rcTile.right = 255;
		rcTile.top = 131;
		rcTile.bottom = 260 + 10;
		break;
	case 6:
		rcTile.left = 201;
		rcTile.right = 245;
		rcTile.top = 285;
		rcTile.bottom = 327 + 5;
		break;
	case 7:
		rcTile.left = 256;
		rcTile.right = 318;
		rcTile.top = 144;
		rcTile.bottom = 263 + 5;
		break;
	case 8:
		rcTile.left = 269;
		rcTile.right = 306;
		rcTile.top = 275;
		rcTile.bottom = 324 + 10;
		break;
	case 9:
		rcTile.left = 320;
		rcTile.right = 383;
		rcTile.top = 153;
		rcTile.bottom = 261 + 5;
		break;
	case 10:
		rcTile.left = 399;
		rcTile.right = 437;
		rcTile.top = 144;
		rcTile.bottom = 205 + 15;
		break;
	case 11:
		rcTile.left = 394;
		rcTile.right = 442;
		rcTile.top = 252;
		rcTile.bottom = 317 + 15;
		break;
	case 12:
		rcTile.left = 458;
		rcTile.right = 496;
		rcTile.top = 144;
		rcTile.bottom = 205 + 15;
		break;
	case 13:
		rcTile.left = 458;
		rcTile.right = 498;
		rcTile.top = 252;
		rcTile.bottom = 317 + 15;
		break;
	case 14:
		rcTile.left = 1;
		rcTile.right = 62;
		rcTile.top = 128;
		rcTile.bottom = 171;
		break;
	case 15:
		rcTile.left = 1;
		rcTile.right = 62;
		rcTile.top = 173;
		rcTile.bottom = 219;
		break;
	case 16:
		rcTile.left = 512;
		rcTile.right = 571;
		rcTile.top = 7;
		rcTile.bottom = 92;
		break;
	case 17:
		rcTile.left = 515;
		rcTile.right = 568;
		rcTile.top = 98;
		rcTile.bottom = 172;
		break;
	case 18:
		rcTile.left = 513;
		rcTile.right = 566;
		rcTile.top = 179;
		rcTile.bottom = 267;
		break;
	case 19:
		rcTile.left = 576;
		rcTile.right = 631;
		rcTile.top = 6;
		rcTile.bottom = 73;
		break;
	case 20:
		rcTile.left = 576;
		rcTile.right = 627;
		rcTile.top = 94;
		rcTile.bottom = 154;
		break;
	case 21:
		rcTile.left = 576;
		rcTile.right = 634;
		rcTile.top = 173;
		rcTile.bottom = 205;
		break;
	case 22:
		rcTile.left = 576;
		rcTile.right = 634;
		rcTile.top = 221;
		rcTile.bottom = 254;
		break;
	case 23:
		rcTile.left = 705;
		rcTile.right = 753;
		rcTile.top = 57;
		rcTile.bottom = 87 + 10;
		break;
	/* 이제부터 타일 간섭 시작(집) */
	case 24:
		rcTile.left = 0;
		rcTile.right = 383;
		rcTile.top = 352;
		rcTile.bottom = 687 - 6;
		break;
	case 25:
		rcTile.left = 384;
		rcTile.right = 767;
		rcTile.top = 352;
		rcTile.bottom = 687 - 6;
		/* 입구를 제외한 모두 이동 불가 */
		break;
	}

	return rcTile;
}

RECT CMaptoolView::GetWarpDraw(int _iDrawID)
{
	RECT rcTile = {};

	/* 뿌리 */
	switch(_iDrawID)
	{
	/* 집 */
	case 1:
		rcTile.left = 32;
		rcTile.top = 208;
		rcTile.right = 47;
		rcTile.bottom = 222;
		break;
	/* 무기점 */
	case 2:
		rcTile.left = 0;
		rcTile.top = 224;
		rcTile.right = 15;
		rcTile.bottom = 239;
		break;
	/* 잡화점 */
	case 3:
		rcTile.left = 160;
		rcTile.top = 224;
		rcTile.right = 175;
		rcTile.bottom = 239;
		break;
	/* 던전 */
	case 4:
		rcTile.left = 64;
		rcTile.top = 208;
		rcTile.right = 78;
		rcTile.bottom = 223;
		break;
	/* 보스 */
	case 5:
		rcTile.left = 81;
		rcTile.top = 208;
		rcTile.right = 94;
		rcTile.bottom = 223;
		break;
	/* 마을 */
	case 6:
		rcTile.left = 256;
		rcTile.top = 225;
		rcTile.right = 271;
		rcTile.bottom = 239;
		break;
	/* 시작점 */
	case 7:
		rcTile.left = 1;
		rcTile.top = 242;
		rcTile.right = 13;
		rcTile.bottom = 254;
		break;
	}

	return rcTile;
}

// CMaptoolView 그리기

void CMaptoolView::OnDraw(CDC* /*pDC*/)
{
	CMaptoolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
		
	D3DXMATRIX	matWorld;

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	
	RECT rcMouse = {65, 0, 65 + TILESIZEX, TILESIZEY};
	//D3DXVECTOR3	vMousePos = D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f);
	D3DXVECTOR3	vMousePos = D3DXVECTOR3(float(point.x), float(point.y), 0.f);
	//TCHAR szTmp[128] = L"";
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	GET_SINGLE(CDevice)->Render_Begin();

	/* 알파 블렌딩 */
	//GET_SINGLE(CDevice)->GetSprite()->End();
	//GET_SINGLE(CDevice)->GetDevice()->EndScene();

	//GET_SINGLE(CDevice)->GetDevice()->BeginScene();
	//GET_SINGLE(CDevice)->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	//GET_SINGLE(CDevice)->GetDevice()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	//GET_SINGLE(CDevice)->GetDevice()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//GET_SINGLE(CDevice)->GetDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	TCHAR szTmp[128] = L"";
	RECT	rcFont = {0};

	for(int y = 0 ; y <= iShowTile * 4; ++y)
	{
		for(int x = 0 ; x <= iShowTile; ++x)
		{
			
			int iIndex = (y + (GetScrollPos(1) / (TILESIZEY / 2))) * TILECNTX + (x + (GetScrollPos(0) / TILESIZEX));	

			if(iIndex >= TILECNTX * TILECNTY || iIndex < 0)
				continue;

			const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Tile");
			if(pTexInfo == NULL)
				continue;
			
			/* 타일 그리기 */
			for(int k = 0 ; k <= m_vecTile[iIndex]->vTilePos.z ; ++k)
			{
				D3DXMatrixTranslation(&matWorld,m_vecTile[iIndex]->vTilePos.x - GetScrollPos(0),
					m_vecTile[iIndex]->vTilePos.y - GetScrollPos(1) - 16 * k, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&GetTileDraw(iIndex),&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));

				D3DXMatrixTranslation(&matWorld,m_vecTile[iIndex]->vRootPos.x - GetScrollPos(0),
					m_vecTile[iIndex]->vRootPos.y - GetScrollPos(1) - 16 * k, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&GetRootDraw(iIndex),&D3DXVECTOR3(TILERTSIZEX / 2.f, TILERTSIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));
			}

			/* 마우스 타일 */
			if(CollisionMouseToTile(vMousePos, m_vecTile[iIndex]))
			{
				/* 마우스 오버 */
				pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"System");
				if(pTexInfo == NULL)
					continue;


				D3DXMatrixTranslation(&matWorld,m_vecTile[iIndex]->vTilePos.x - GetScrollPos(0),
					m_vecTile[iIndex]->vTilePos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rcMouse,&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));
			}
						
			/* 오브젝트 그리기 */
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Tile");
			if(pTexInfo == NULL)
				continue;

			for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
			{
				if((*iterObj)->vObjPos.x == m_vecTile[iIndex]->vTilePos.x &&
					(*iterObj)->vObjPos.y == m_vecTile[iIndex]->vTilePos.y)
				{
					/* 타일 높이 조절(집 배치) */
					if((*iterObj)->byDrawId == 24)
					{
						int iTmpI, iTmpJ;

						/* 좌측 상단 기준으로 확장 */
						for(int i = 0 ; i < 6 ; ++i)
						{
							if(i == 0)
								iTmpI = iIndex;
							else
							{
								iTmpI = iTmpI - (TILECNTX + 1 - (iTmpI / TILECNTX) % 2);
							}
							/* 우측 상단 기준으로 확장 */
							for(int  j = 0 ; j < 6 ; ++j)
							{
								if(j == 0)
									iTmpJ = iTmpI;
								else if(j == 1)
									iTmpJ  = iTmpI - (TILECNTX - (iTmpI/TILECNTX) % 2);
								else
									iTmpJ = iTmpJ - (TILECNTX - (iTmpJ/TILECNTX) % 2);

								if((i == 0 && j == 0) || (i == 3 && j == 0))
									continue;
								
								if(iTmpI > 0 && iTmpJ > 0)
									m_vecTile[iTmpJ]->vTilePos.z = -1.f;
							}
						}
					}
					else if((*iterObj)->byDrawId == 25)
					{
						int iTmpI, iTmpJ;

						/* 좌측 상단 기준으로 확장 */
						for(int i = 0 ; i < 6 ; ++i)
						{
							if(i == 0)
								iTmpI = iIndex;
							else
							{
								iTmpI = iTmpI - (TILECNTX + 1 - (iTmpI / TILECNTX) % 2);
							}
							/* 우측 상단 기준으로 확장 */
							for(int  j = 0 ; j < 6 ; ++j)
							{
								if(j == 0)
									iTmpJ = iTmpI;
								else if(j == 1)
									iTmpJ  = iTmpI - (TILECNTX - (iTmpI / TILECNTX) % 2);
								else
									iTmpJ = iTmpJ - (TILECNTX - (iTmpJ / TILECNTX) % 2);

								if((i == 0 && j == 0) || (i == 0 && j == 3))
									continue;
								if(iTmpI > 0 && iTmpJ > 0)
									m_vecTile[iTmpJ]->vTilePos.z = -1.f;
							}
						}
					}
					
					D3DXMatrixTranslation(&matWorld,(*iterObj)->vObjPos.x - GetScrollPos(0),
						(*iterObj)->vObjPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &GetObjDraw((*iterObj)->byDrawId), 
						&D3DXVECTOR3((GetObjDraw((*iterObj)->byDrawId).right - GetObjDraw((*iterObj)->byDrawId).left) / 2.f, 
						(GetObjDraw((*iterObj)->byDrawId).bottom - GetObjDraw((*iterObj)->byDrawId).top) - TILESIZEY / 2.f, 0.f),
						NULL,D3DCOLOR_ARGB(255,255,255,255));
				}
			}

			/* 몬스터 그리기 */
			for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
			{
				if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
					(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
				{
					RECT rc = { 0, 0, 100, 100};					//소형 몬스터
					RECT rcUpper = { 0, 0, 233, 129};				//대형 몬스터 상체
					RECT rcLower = { 0, 0, 272, 159};				//대형 몬스터 하체
					switch((*iterMon)->byDrawId)
					{
					case 1:
						//고블린
						pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Goblin", L"Monster", (*iterMon)->byDrawId);
						if(pTexInfo == NULL)
							continue;
						D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x - GetScrollPos(0),
							(*iterMon)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
						GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
						GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
							&rc,&(*iterMon)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
						break;
					case 2:			
						//슬라임
						pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Slime", L"Monster", (*iterMon)->byDrawId);
						if(pTexInfo == NULL)
							continue;
						D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x - GetScrollPos(0),
							(*iterMon)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
						GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
						GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
							&rc,&(*iterMon)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
						break;
				case 3:
					//대형 몬스터(타락천사)
					/* 상체 */
					pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Boss", L"Monster", 4);
					if(pTexInfo == NULL)
						continue;
					D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x - GetScrollPos(0),
						(*iterMon)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
						&rcUpper,&D3DXVECTOR3( 71, 287.f, 0.f),NULL,D3DCOLOR_ARGB(255,255,255,255));
					/* 하체 */
					pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Boss", L"Monster", 0);
					if(pTexInfo == NULL)
						continue;
					D3DXMatrixTranslation(&(*iterMon)->tObjInfo.matWorld,(*iterMon)->tObjInfo.vPos.x - GetScrollPos(0),
						(*iterMon)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterMon)->tObjInfo.matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
						&rcLower,&D3DXVECTOR3( 78, 159.f, 0.f),NULL,D3DCOLOR_ARGB(255,255,255,255));
					break;
					}
				}
			}

			/* NPC 그리기 */
			for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
			{
				if((*iterNPC)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
					(*iterNPC)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
				{
					RECT rc = {(*iterNPC)->iStartDir % 2 * 100, 0, rc.left + 100, 100};			
					switch((*iterNPC)->byDrawId)
					{
					case 1:
						//천사
						pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Angel", L"NPC");
						if(pTexInfo == NULL)
							continue;
						switch((*iterNPC)->iStartDir)
						{
						case 0:
						case 1:
							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						case 2:
						case 3:
							D3DXMATRIX matScale;
							D3DXMatrixIdentity(&matScale);
							D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);

							(*iterNPC)->tObjInfo.matWorld = matScale * (*iterNPC)->tObjInfo.matWorld;

							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						}
						break;
					case 2:
						//엘프
						pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Elf", L"NPC");
						if(pTexInfo == NULL)
							continue;
						switch((*iterNPC)->iStartDir)
						{
						case 0:
						case 1:
							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						case 2:
						case 3:
							D3DXMATRIX matScale;
							D3DXMatrixIdentity(&matScale);
							D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);

							(*iterNPC)->tObjInfo.matWorld = matScale * (*iterNPC)->tObjInfo.matWorld;

							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						}
						break;
					case 3:
						//여성
						pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Woman", L"NPC");
						if(pTexInfo == NULL)
							continue;
						switch((*iterNPC)->iStartDir)
						{
						case 0:
						case 1:
							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						case 2:
						case 3:
							D3DXMATRIX matScale;
							D3DXMatrixIdentity(&matScale);
							D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

							D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x - GetScrollPos(0),
								(*iterNPC)->tObjInfo.vPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);

							(*iterNPC)->tObjInfo.matWorld = matScale * (*iterNPC)->tObjInfo.matWorld;

							GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
							GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
								&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
							break;
						}
						break;
					}
				}
			}

			/* 워프 그리기 */
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Warp");
			if(pTexInfo == NULL)
				continue;

			for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
			{
				if((*iterSys)->vSysPos.x == m_vecTile[iIndex]->vTilePos.x &&
					(*iterSys)->vSysPos.y == m_vecTile[iIndex]->vTilePos.y)
				{
					D3DXMatrixTranslation(&matWorld,(*iterSys)->vSysPos.x - GetScrollPos(0),
						(*iterSys)->vSysPos.y - GetScrollPos(1) - 16 * m_vecTile[iIndex]->vTilePos.z, 0.f);
					GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
					GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &GetWarpDraw((*iterSys)->byDrawId), 
						&D3DXVECTOR3((GetWarpDraw((*iterSys)->byDrawId).right - GetWarpDraw((*iterSys)->byDrawId).left) / 2.f, 
						float(GetWarpDraw((*iterSys)->byDrawId).bottom - GetWarpDraw((*iterSys)->byDrawId).top), 0.f),
						NULL,D3DCOLOR_ARGB(255,255,255,255));
				}
			}

			//wsprintf(szTmp,L"%d",iIndex);
			//GET_SINGLE(CDevice)->GetFont()->DrawTextW(GET_SINGLE(CDevice)->GetSprite(),
			//	szTmp,lstrlen(szTmp),&rcFont,DT_NOCLIP,D3DCOLOR_ARGB(255,0,0,0));
		}
	}

	/* 알파 블렌딩 끝 */
	//GET_SINGLE(CDevice)->GetSprite()->End();
	//GET_SINGLE(CDevice)->GetDevice()->EndScene();

	//GET_SINGLE(CDevice)->GetDevice()->BeginScene();
	//GET_SINGLE(CDevice)->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	
	D3DXMATRIX matWorld2;
	D3DXMatrixTranslation(&matWorld2, point.x, point.y, 0.f);
	TCHAR szTmp2[128] = L"↖";
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld2);
	RECT	rcFont2 = { 0 };
	GET_SINGLE(CDevice)->GetFont()->DrawTextW(GET_SINGLE(CDevice)->GetSprite(), szTmp2, lstrlen(szTmp2), &rcFont2, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));


	GET_SINGLE(CDevice)->Render_End(m_hWnd);
	m_pMiniMap->Invalidate(FALSE);
}

/* 실행될 때 최초로 한번 실행되는 함수 */
void CMaptoolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT,CSize(TILESIZEX * TILECNTX, (TILESIZEY * TILECNTY / 2)));
	SetScrollPos(0,0);

	if(FAILED(GET_SINGLE(CDevice)->InitDevice(m_hWnd)))
	{
		return;
	}

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/* 타일 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 255, L"../Resource/Texture/Map/MapEx.png",L"Tile",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	
	/* 마우스 커서 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 0, L"../Resource/Texture/System/System.png",L"System",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	
	/* 워프 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 128, 0, 128, L"../Resource/Texture/System/Wall.png",L"Warp",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	
	/* 고블린 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Goblin.png",L"Goblin",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	
	/* 슬라임 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Slime.png",L"Slime",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}

	/* 타락천사 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Boss/Boss%d.png",L"Boss",
		TEXTTYPE_MULTI, L"Monster", 19)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
		
	/* 천사 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Angel.png",L"Angel",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}	

	/* 엘프 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Elf.png",L"Elf",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}	

	/* 여자 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Woman.png",L"Woman",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	
	/* 미니맵용 */
	/* 몬스터 */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 255, 255, L"../Resource/Texture/Monster/Mon_MiniMap.png",L"Mon_MiniMap",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}
	/* NPC */
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 255, 255, L"../Resource/Texture/Monster/NPC_MiniMap.png",L"NPC_MiniMap",
		TEXTTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패");
		return;
	}

	InitTile();
	InitObj();
	InitSystem();
	InitMonster();
	InitNPC();

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	RECT	rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);
	SetRect(&rcWindow,0,0,rcWindow.right - rcWindow.left,rcWindow.bottom-rcWindow.top);
	RECT	rcMainView;
	GetClientRect(&rcMainView);

	int iRowFrm = rcWindow.bottom - rcMainView.bottom;
	int iColFrm = rcWindow.right - rcMainView.right;

	pMainFrm->SetWindowPos(NULL,0,0,WINSIZEX+iColFrm,WINSIZEY+iRowFrm,SWP_NOZORDER);
}

// CMaptoolView 인쇄

void CMaptoolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMaptoolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMaptoolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMaptoolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMaptoolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMaptoolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMaptoolView 진단

#ifdef _DEBUG
void CMaptoolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMaptoolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMaptoolDoc* CMaptoolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaptoolDoc)));
	return (CMaptoolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMaptoolView 메시지 처리기


BOOL CMaptoolView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

void CMaptoolView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GET_SINGLE(CTextureMgr)->DestroyInstance();
	GET_SINGLE(CDevice)->DestroyInstance();

	for(size_t i = 0 ; i < m_vecTile.size() ; ++i)
	{
		delete m_vecTile[i];
		m_vecTile[i] = NULL;
	}
	m_vecTile.clear();

	for(size_t i = 0 ; i < m_vecSys.size() ; ++i)
	{
		delete m_vecSys[i];
		m_vecSys[i] = NULL;
	}
	m_vecSys.clear();
	
	for(size_t i = 0 ; i < m_vecObj.size() ; ++i)
	{
		delete m_vecObj[i];
		m_vecObj[i] = NULL;
	}
	m_vecObj.clear();
	
	for(size_t i = 0 ; i < m_vecMon.size() ; ++i)
	{
		delete m_vecMon[i];
		m_vecMon[i] = NULL;
	}
	m_vecMon.clear();
	
	for(size_t i = 0 ; i < m_vecNPC.size() ; ++i)
	{
		delete m_vecNPC[i];
		m_vecNPC[i] = NULL;
	}
	m_vecNPC.clear();
}

void CMaptoolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int iIndex = 0;
	
	D3DXVECTOR3	vMousePos = D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f);

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(CollisionMouseToTile(vMousePos,m_vecTile[i]))
		{
			iIndex = i;
			/* 타일 배치 */
			if(m_iSelectTileID >= 0)
				m_vecTile[iIndex]->byDrawId = m_iSelectTileID;
			/* 오브젝트 배치 */
			if(m_iSelectObjID > 0)
			{
				/* 오브젝트는 모든 물체를 삭제하고 배치함 */
				/* 오브젝트 삭제 */
				for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
				{
					if((*iterObj)->vObjPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterObj)->vObjPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterObj);
						iterObj = m_vecObj.erase(iterObj);
						break;
					}
				}
				/* 몬스터 삭제 */
				for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
				{
					if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterMon);
						iterMon = m_vecMon.erase(iterMon);
						break;
					}
				}
				/* NPC 삭제 */
				for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
				{
					if((*iterNPC)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterNPC)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterNPC);
						iterNPC = m_vecNPC.erase(iterNPC);
						break;
					}
				}
				/* 워프 삭제 */
				for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
				{
					if((*iterSys)->vSysPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterSys)->vSysPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterSys);
						iterSys = m_vecSys.erase(iterSys);
						break;
					}
				}
				/* 오브젝트 추가 */
				if(m_vecTile[iIndex]->vTilePos.z > -1)
				{
					OBJECT* pObj = new OBJECT;
					pObj->byDrawId = m_iSelectObjID;
					pObj->vObjPos.x = m_vecTile[iIndex]->vTilePos.x;
					pObj->vObjPos.y = m_vecTile[iIndex]->vTilePos.y;
					pObj->vObjPos.z = 0.f;
					m_vecObj.push_back(pObj);
				}
			}
			/* 몬스터 배치 */
			if(m_iSelectMonsterID > 0)
			{
				/* 해당 위치에 기존 몬스터 삭제 */
				for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
				{
					if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterMon);
						iterMon = m_vecMon.erase(iterMon);
						break;
					}
				}

				/* 몬스터 추가 */
				if(m_vecTile[iIndex]->vTilePos.z > -1 && m_MonsterClass != MONSTER_CLASS_NULL)
				{
					MONSTER* pMon = new MONSTER;
					pMon->tObjInfo.vPos.x = m_vecTile[iIndex]->vTilePos.x;
					pMon->tObjInfo.vPos.y = m_vecTile[iIndex]->vTilePos.y;
					pMon->tObjInfo.vPos.z = 0.f;
					pMon->eClass = m_MonsterClass;
					pMon->tInfo.iAttack = m_iAttack;
					pMon->tInfo.iHP = m_iHP;
					pMon->tInfo.iCurHP = pMon->tInfo.iHP;
					pMon->tInfo.iMP = m_iMP;
					pMon->tInfo.iCurMP = pMon->tInfo.iMP;
					pMon->tInfo.iDefence = m_iDefence;
					pMon->tInfo.iExp = m_iExp;
					pMon->tInfo.iCurExp = pMon->tInfo.iExp;
					pMon->tInfo.iMoney = m_iMoney;
					pMon->byDrawId = m_iSelectMonsterID;
					/* DrawID에 따른 Center 지정 */
					switch(pMon->byDrawId)
					{
					case 1:
						pMon->tObjInfo.vCenter = D3DXVECTOR3(50.f, 90.f, 0.f);
						break;
					case 2:
						pMon->tObjInfo.vCenter = D3DXVECTOR3(50.f, 80.f, 0.f);
						break;
					}
					m_vecMon.push_back(pMon);

					
					/* 해당 위치에 오브젝트가 있으면 추가된 몬스터 삭제(추가X) */
					for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
					{
						if(m_vecMon.back()->tObjInfo.vPos.x == (*iterObj)->vObjPos.x &&
							m_vecMon.back()->tObjInfo.vPos.y == (*iterObj)->vObjPos.y)
						{
							m_vecMon.pop_back();
							break;
						}
					}

					/* 해당 위치에 NPC가 있으면 추가된 몬스터 삭제(추가X) */
					for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
					{
						if(m_vecMon.back()->tObjInfo.vPos.x == (*iterNPC)->tObjInfo.vPos.x &&
							m_vecMon.back()->tObjInfo.vPos.y == (*iterNPC)->tObjInfo.vPos.y)
						{
							m_vecMon.pop_back();
							break;
						}
					}
				}
			}
			/* NPC 배치 */
			if(m_iSelectNPCID > 0)
			{
				/* 해당 위치에 NPC 방향 바꾸기 아니면 삭제 */
				/* NPC가 없을 경우 추가 */
				if(m_vecNPC.empty())
				{
					/* NPC 추가 */
					if(m_vecTile[iIndex]->vTilePos.z > -1 && m_NPCClass != NPC_CLASS_NULL)
					{

						/* 해당 위치에 몬스터 삭제 */
						for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
						{
							if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
								(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
							{
								SAFE_DELETE(*iterMon);
								iterMon = m_vecMon.erase(iterMon);
								break;
							}
						}

						NPC* pNPC = new NPC;
						pNPC->tObjInfo.vPos.x = m_vecTile[iIndex]->vTilePos.x;
						pNPC->tObjInfo.vPos.y = m_vecTile[iIndex]->vTilePos.y;
						pNPC->tObjInfo.vPos.z = 0.f;
						pNPC->eClass = m_NPCClass;
						pNPC->byDrawId = m_iSelectNPCID;
						pNPC->iStartDir = 0;
						switch(pNPC->byDrawId)
						{
						case 1:
							pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 80.f, 0.f);
							break;
						case 2:
							pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 70.f, 0.f);
							break;
						case 3:
							pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 75.f, 0.f);
							break;
						}
						m_vecNPC.push_back(pNPC);
														
						/* 해당 위치에 오브젝트가 있으면 추가된 NPC 삭제(추가X) */
						for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
						{
							if(m_vecNPC.back()->tObjInfo.vPos.x == (*iterObj)->vObjPos.x &&
								m_vecNPC.back()->tObjInfo.vPos.y == (*iterObj)->vObjPos.y)
							{
								m_vecNPC.pop_back();
								break;
							}
						}
					}
				}
				else
				{
					/* 가라성 변수 */
					bool isChanged = false;

					for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
					{
						if((*iterNPC)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterNPC)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							if((*iterNPC)->byDrawId == m_iSelectNPCID)
							{
								++(*iterNPC)->iStartDir;
								if((*iterNPC)->iStartDir > 3)
									(*iterNPC)->iStartDir = 0;
								isChanged = true;
							}
							else
							{
								/* 기존에 있는 NPC 삭제 */
								SAFE_DELETE(*iterNPC);
								iterNPC = m_vecNPC.erase(iterNPC);
							}
							break;
						}
					}
					
					if(!isChanged)
					{
						/* NPC 추가 */
						if(m_vecTile[iIndex]->vTilePos.z > -1 && m_NPCClass != NPC_CLASS_NULL)
						{

							/* 해당 위치에 몬스터 삭제 */
							for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
							{
								if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
									(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
								{
									SAFE_DELETE(*iterMon);
									iterMon = m_vecMon.erase(iterMon);
									break;
								}
							}

							NPC* pNPC = new NPC;
							pNPC->tObjInfo.vPos.x = m_vecTile[iIndex]->vTilePos.x;
							pNPC->tObjInfo.vPos.y = m_vecTile[iIndex]->vTilePos.y;
							pNPC->tObjInfo.vPos.z = 0.f;
							pNPC->byDrawId = m_iSelectNPCID;
							pNPC->eClass = m_NPCClass;
							pNPC->iStartDir = 0;
							switch(pNPC->byDrawId)
							{
							case 1:
								pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 80.f, 0.f);
								break;
							case 2:
								pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 70.f, 0.f);
								break;
							case 3:
								pNPC->tObjInfo.vCenter = D3DXVECTOR3( 45.f, 75.f, 0.f);
								break;
							}
							m_vecNPC.push_back(pNPC);
														
							/* 해당 위치에 오브젝트가 있으면 추가된 NPC 삭제(추가X) */
							for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
							{
								if(m_vecNPC.back()->tObjInfo.vPos.x == (*iterObj)->vObjPos.x &&
									m_vecNPC.back()->tObjInfo.vPos.y == (*iterObj)->vObjPos.y)
								{
									m_vecNPC.pop_back();
									break;
								}
							}
						}
					}
				}
			}
			/* 워프 배치 */
			if(m_iSelectWarpID > 0)
			{
				/* 해당 위치에 기존 워프 삭제 */
				for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
				{
					if((*iterSys)->vSysPos.x == m_vecTile[iIndex]->vTilePos.x &&
						(*iterSys)->vSysPos.y == m_vecTile[iIndex]->vTilePos.y)
					{
						SAFE_DELETE(*iterSys);
						iterSys = m_vecSys.erase(iterSys);
						break;
					}
				}
				/* 워프 추가 */
				if(m_vecTile[iIndex]->vTilePos.z > -1)
				{
					SYSTEM* pSys = new SYSTEM;
					pSys->vSysPos.x = m_vecTile[iIndex]->vTilePos.x;
					pSys->vSysPos.y = m_vecTile[iIndex]->vTilePos.y;
					pSys->vSysPos.z = 0.f;
					pSys->byDrawId = m_iSelectWarpID;
					m_vecSys.push_back(pSys);
						
					/* 해당 위치에 오브젝트가 있으면 추가된 워프 삭제(추가X) */
					for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
					{
						if(m_vecSys.back()->vSysPos.x == (*iterObj)->vObjPos.x &&
							m_vecSys.back()->vSysPos.y == (*iterObj)->vObjPos.y)
						{
							m_vecSys.pop_back();
							break;
						}
					}

					/* 7번 워프(귀환)가 이미 존재할 경우 삭제 */
					if(m_iSelectWarpID == 7)
					{
						for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() - 1 ; ++iterSys)
						{
							if((*iterSys)->byDrawId == 7)
							{
								SAFE_DELETE(*iterSys);
								iterSys = m_vecSys.erase(iterSys);
								break;
							}
						}
					}
				}

			}
			break;
		}
	}
	Invalidate(FALSE);
	CScrollView::OnLButtonDown(nFlags, point);
}

BOOL CMaptoolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int iIndex = 0;

	ScreenToClient(&pt);
	D3DXVECTOR3	vMousePos = D3DXVECTOR3(float(pt.x + GetScrollPos(0)), float(pt.y + GetScrollPos(1)), 0.f);

	/* 마우스 휠 다운 */
	if(zDelta < 0)
	{
		for(size_t i = 0 ; i < m_vecTile.size() ; ++i)
		{
			if(CollisionMouseToTile(vMousePos,m_vecTile[i]))
			{
				iIndex = i;

				/* 해당 타일 높이 낮춤 */
				if(m_vecTile[i]->vTilePos.z > -1)
				{
					--m_vecTile[i]->vTilePos.z;
					--m_vecTile[i]->vRootPos.z;
					/* 해당 타일의 높이가 -1일 경우 모든 물체 삭제 */
					if(m_vecTile[i]->vTilePos.z == -1)
					{
						/* 워프 삭제 */
						for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
						{
							if((*iterSys)->vSysPos.x == m_vecTile[iIndex]->vTilePos.x &&
								(*iterSys)->vSysPos.y == m_vecTile[iIndex]->vTilePos.y)
							{
								SAFE_DELETE(*iterSys);
								iterSys = m_vecSys.erase(iterSys);
								break;
							}
						}
						/* 오브젝트 삭제 */
						for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
						{
							if((*iterObj)->vObjPos.x == m_vecTile[iIndex]->vTilePos.x &&
								(*iterObj)->vObjPos.y == m_vecTile[iIndex]->vTilePos.y)
							{
								SAFE_DELETE(*iterObj);
								iterObj = m_vecObj.erase(iterObj);
								break;
							}
						}
						/* 몬스터 삭제 */
						for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
						{
							if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
								(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
							{
								SAFE_DELETE(*iterMon);
								iterMon = m_vecMon.erase(iterMon);
								break;
							}
						}
						/* NPC 삭제 */
						for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
						{
							if((*iterNPC)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
								(*iterNPC)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
							{
								SAFE_DELETE(*iterNPC);
								iterNPC = m_vecNPC.erase(iterNPC);
								break;
							}
						}
					}
				}
			}
		}
		m_pMiniMap->Invalidate(FALSE);
		Invalidate(FALSE);
	}
	/* 휠 업 */
	else
	{
		for(size_t i = 0 ; i < m_vecTile.size() ; ++i)
		{
			if(CollisionMouseToTile(vMousePos,m_vecTile[i]))
			{
				/* 해당 타일 높이 낮춤 */
				if(m_vecTile[i]->vTilePos.z < 5)
				{
					++m_vecTile[i]->vTilePos.z;
					++m_vecTile[i]->vRootPos.z;
				}
			}
		}
		m_pMiniMap->Invalidate(FALSE);
		Invalidate(FALSE);
	}

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMaptoolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		int iIndex = 0;
		
		D3DXVECTOR3	vMousePos = D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f);

		for (size_t i = 0; i < m_vecTile.size(); ++i)
		{
			if(CollisionMouseToTile(vMousePos,m_vecTile[i]))
			{
				iIndex = i;
				/* 타일 배치 */
				if(m_iSelectTileID >= 0)
					m_vecTile[iIndex]->byDrawId = m_iSelectTileID;
				/* 오브젝트 배치 */
				if(m_iSelectObjID > 0)
				{
					/* 오브젝트는 모든 물체를 삭제하고 배치함 */
					/* 오브젝트 삭제 */
					for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
					{
						if((*iterObj)->vObjPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterObj)->vObjPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							SAFE_DELETE(*iterObj);
							iterObj = m_vecObj.erase(iterObj);
							break;
						}
					}
					/* 몬스터 삭제 */
					for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
					{
						if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							SAFE_DELETE(*iterMon);
							iterMon = m_vecMon.erase(iterMon);
							break;
						}
					}
					/* NPC 삭제 */
					for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
					{
						if((*iterNPC)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterNPC)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							SAFE_DELETE(*iterNPC);
							iterNPC = m_vecNPC.erase(iterNPC);
							break;
						}
					}
					/* 워프 삭제 */
					for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
					{
						if((*iterSys)->vSysPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterSys)->vSysPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							SAFE_DELETE(*iterSys);
							iterSys = m_vecSys.erase(iterSys);
							break;
						}
					}
					/* 오브젝트 추가 */
					if(m_vecTile[iIndex]->vTilePos.z > -1)
					{
						OBJECT* pObj = new OBJECT;
						pObj->byDrawId = m_iSelectObjID;
						pObj->vObjPos.x = m_vecTile[iIndex]->vTilePos.x;
						pObj->vObjPos.y = m_vecTile[iIndex]->vTilePos.y;
						pObj->vObjPos.z = 0.f;
						m_vecObj.push_back(pObj);
					}
				}
				/* 몬스터 배치 */
				if(m_iSelectMonsterID > 0)
				{
					/* 해당 위치에 기존 몬스터 삭제 */
					for(vector<MONSTER*>::iterator iterMon = m_vecMon.begin() ; iterMon != m_vecMon.end() ; ++iterMon)
					{
						if((*iterMon)->tObjInfo.vPos.x == m_vecTile[iIndex]->vTilePos.x &&
							(*iterMon)->tObjInfo.vPos.y == m_vecTile[iIndex]->vTilePos.y)
						{
							SAFE_DELETE(*iterMon);
							iterMon = m_vecMon.erase(iterMon);
							break;
						}
					}

					/* 몬스터 추가 */
					if(m_vecTile[iIndex]->vTilePos.z > -1 && m_MonsterClass != MONSTER_CLASS_NULL)
					{
						MONSTER* pMon = new MONSTER;
						pMon->tObjInfo.vPos.x = m_vecTile[iIndex]->vTilePos.x;
						pMon->tObjInfo.vPos.y = m_vecTile[iIndex]->vTilePos.y;
						pMon->tObjInfo.vPos.z = 0.f;
						pMon->eClass = m_MonsterClass;
						pMon->tInfo.iAttack = m_iAttack;
						pMon->tInfo.iHP = m_iHP;
						pMon->tInfo.iCurHP = pMon->tInfo.iHP;
						pMon->tInfo.iMP = m_iMP;
						pMon->tInfo.iCurMP = pMon->tInfo.iMP;
						pMon->tInfo.iDefence = m_iDefence;
						pMon->tInfo.iExp = m_iExp;
						pMon->tInfo.iCurExp = pMon->tInfo.iExp;
						pMon->tInfo.iMoney = m_iMoney;
						pMon->byDrawId = m_iSelectMonsterID;
						/* DrawID에 따른 Center 지정 */
						switch(pMon->byDrawId)
						{
						case 1:
							pMon->tObjInfo.vCenter = D3DXVECTOR3(50.f, 90.f, 0.f);
							break;
						case 2:
							pMon->tObjInfo.vCenter = D3DXVECTOR3(50.f, 80.f, 0.f);
							break;
						}
						m_vecMon.push_back(pMon);

					
						/* 해당 위치에 오브젝트가 있으면 추가된 몬스터 삭제(추가X) */
						for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
						{
							if(m_vecMon.back()->tObjInfo.vPos.x == (*iterObj)->vObjPos.x &&
								m_vecMon.back()->tObjInfo.vPos.y == (*iterObj)->vObjPos.y)
							{
								m_vecMon.pop_back();
								break;
							}
						}

						/* 해당 위치에 NPC가 있으면 추가된 몬스터 삭제(추가X) */
						for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
						{
							if(m_vecMon.back()->tObjInfo.vPos.x == (*iterNPC)->tObjInfo.vPos.x &&
								m_vecMon.back()->tObjInfo.vPos.y == (*iterNPC)->tObjInfo.vPos.y)
							{
								m_vecMon.pop_back();
								break;
							}
						}
					}
				}
			}
		}
	}				
	Invalidate(FALSE);
	CScrollView::OnMouseMove(nFlags, point);
}
