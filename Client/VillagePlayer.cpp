#include "StdAfx.h"
#include "VillagePlayer.h"

#include "TextureMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AStar.h"
#include "VillageMap.h"

CVillagePlayer::CVillagePlayer(void)
{
}

CVillagePlayer::CVillagePlayer(const OBJ_INFO& _Info)
	:CVillageDynamic(_Info)
{
}

CVillagePlayer::~CVillagePlayer(void)
{
	Release();
}

void CVillagePlayer::InitPlayerFromFile()
{

}

HRESULT	CVillagePlayer::Initialize(void)
{
	m_pObjKey = L"Karin";
	m_SortID = SORT_ID_PLAYER;

	m_bClicked = false;

	m_Info.vPos = m_vOffset;
	m_Info.vCenter	= D3DXVECTOR3(50.f, 80.f, 0.f);
	m_Info.vDir		= D3DXVECTOR3(50.f, 80.f, 0.f);
	m_Info.vLook	= D3DXVECTOR3(1.f, 1.f, 0.f);
	m_Info.vSize	= D3DXVECTOR3(1.f, 0.f, 0.f);

	m_vScroll = D3DXVECTOR3(WINSIZEX / 2.f - m_Info.vPos.x, WINSIZEY / 2.f -  m_Info.vPos.y, 0.f);

	m_Player.dwState = STATE_STAND;
	
	m_Player.tInfo.iLevel = 1;
	m_Player.tInfo.iHP = m_Player.tInfo.iCurHP = 100;
	m_Player.tInfo.iMP = m_Player.tInfo.iCurMP = 100;
	m_Player.tInfo.iAttack = 10;
	m_Player.tInfo.iDefence = 0;
	m_Player.tInfo.iCurExp = 0;
	m_Player.tInfo.iExp = 100;
	m_Player.tInfo.iMoney = 0;

	return S_OK;
}

bool CompareTileForPlayer(TILE* a, TILE* b)
{
	return (*a).vTilePos.y > (*b).vTilePos.y;
}

void CVillagePlayer::KeyCheck( void )
{
	if(PUSH_KEY(KEY_LBUTTON))
	{
		if(m_bClicked == true)
			return;
		m_bClicked = true;

		if(!GET_SINGLE(CObjMgr)->GetTmpInfo()->empty())
			AStar_Start(m_Info.vPos + *GetScroll(), (*GET_SINGLE(CObjMgr)->GetTmpInfo()->begin())->vTilePos + *GetScroll());
	}

	if(UP_KEY(KEY_LBUTTON))
		m_bClicked = false;
}

SCENE CVillagePlayer::Progress(void)
{

	AStar_Move();
	KeyCheck();
	OnScroll();
	Single_Frame_Move(5);
	Motion();

	/* 플레이어 이동 여부 */
	list<int>* pBestList = GET_SINGLE(CAStar)->GetBestList();
	if(pBestList->empty())
		m_Player.dwState = STATE_STAND;
	else
	{	
		m_Player.dwState = STATE_MOVE;
	}
	
	/* 플레이어 위치 구하기 */
	D3DXMATRIX matTrans;
	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(size_t i = 0 ; i < pvecTile->size() ; ++i)
	{
		if(m_Info.vPos.x == (*pvecTile)[i]->vTilePos.x 
			&& m_Info.vPos.y == (*pvecTile)[i]->vTilePos.y)
		{
			m_Info.vPos.z = (*pvecTile)[i]->vTilePos.z;
			break;
		}
	}

	D3DXMatrixTranslation(&matTrans,m_Info.vPos.x + m_vScroll.x, m_Info.vPos.y + m_vScroll.y - 16 * m_Info.vPos.z, 0.f);
	m_Info.matWorld =  matTrans;

	return SCENE_NONPASS;
}

RECT CVillagePlayer::GetTileDraw(int _iIndex)
{
	RECT rcTile = {};

	switch((*GET_SINGLE(CObjMgr)->GetTileInfo())[_iIndex]->byDrawId)
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

RECT CVillagePlayer::GetRootDraw(int _iIndex)
{
	RECT rcTile = {};

	/* 뿌리 */
	switch((*GET_SINGLE(CObjMgr)->GetTileInfo())[_iIndex]->byDrawId)
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

void CVillagePlayer::Render(void)
{
	const TEXINFO*	pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
	if(pTexInfo == NULL)
		return;

	RECT Frame = { 100 * (int)m_tFrame.fStart, 100 * m_tFrame.iScene, Frame.left + 100, Frame.top + 100};

	/* 좌우 반전 */ 
	if((m_Info.vDir.x > 0 && m_Info.vDir.y > 0) || (m_Info.vDir.x < 0 && m_Info.vDir.y < 0))
	{
		D3DXMATRIX matScale;
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
		m_Info.matWorld = matScale * m_Info.matWorld;
	}

	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,&Frame,
		&m_Info.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));

	/* 플레이어 정보 출력 */
	TCHAR szTmp[128] = L"";	
	RECT	rcFont = {0};

	/*wsprintf(szTmp,L"Offset(%d / %d / %d)\nScroll(%d / %d / %d)\nvPos(%d / %d / %d)\n", 
		(int)m_vOffset.x, (int)m_vOffset.y, (int)m_vOffset.z,
		(int)m_vScroll.x, (int)m_vScroll.y, (int)m_vScroll.z,
		(int)m_Info.vPos.x, (int)m_Info.vPos.y, (int)m_Info.vPos.z);	*/		
	/*wsprintf(szTmp,L"fStart : %d\nfLast : %d\niScene : %d\n", 
		(int)m_tFrame.fStart, (int)m_tFrame.fLast, (int)m_tFrame.iScene);*/
	GET_SINGLE(CDevice)->GetFont()->DrawTextW(GET_SINGLE(CDevice)->GetSprite(),
		szTmp,lstrlen(szTmp),&rcFont,DT_NOCLIP,D3DCOLOR_ARGB(255,0,0,0));
}

void CVillagePlayer::Release(void)
{

}

CObj* CVillagePlayer::Clone(void)
{
	return new CVillagePlayer(*this);
}

void CVillagePlayer::OnScroll()
{
	if(m_Info.vPos.x != m_vOffset.x
		&& m_Info.vPos.y != m_vOffset.y)
	{
		m_vScroll.x -= m_Info.vPos.x - m_vOffset.x;
		m_vScroll.y -= m_Info.vPos.y - m_vOffset.y;
		m_vOffset = m_Info.vPos;
	}
}

void CVillagePlayer::Motion()
{
	/* 대기 */
	if(m_Player.dwState & STATE_STAND)
	{
		//우측 하단
		if(m_Info.vDir.x > 0  && m_Info.vDir.y > 0)
			SetScene(4,0);
		//우측 상단
		if(m_Info.vDir.x > 0  && m_Info.vDir.y < 0)
			SetScene(4,1);
		//좌측 상단
		if(m_Info.vDir.x < 0  && m_Info.vDir.y < 0)
			SetScene(4,1);
		//좌측 하단
		if(m_Info.vDir.x < 0  && m_Info.vDir.y > 0)
			SetScene(4,0);
	}
	/* 이동 */
	if(m_Player.dwState & STATE_MOVE)
	{
		//우측 하단
		if(m_Info.vDir.x > 0  && m_Info.vDir.y > 0)
			SetScene(3,2);
		//우측 상단
		if(m_Info.vDir.x > 0  && m_Info.vDir.y < 0)
			SetScene(3,3);
		//좌측 상단
		if(m_Info.vDir.x < 0  && m_Info.vDir.y < 0)
			SetScene(3,3);
		//좌측 하단
		if(m_Info.vDir.x < 0  && m_Info.vDir.y > 0)
			SetScene(3,2);
	}
}