#include "StdAfx.h"
#include "VillageWarp.h"

#include "TextureMgr.h"
#include "ObjMgr.h"

CVillageWarp::CVillageWarp(void)
{
}

CVillageWarp::CVillageWarp(const OBJ_INFO& _Info)
	:CVillageStatic(_Info)
{
}

CVillageWarp::~CVillageWarp(void)
{
	Release();
}


HRESULT	CVillageWarp::Initialize(void)
{
	m_pObjKey = L"Warp";
	m_SortID = SORT_ID_WARP;

	InitSysFromFile();

	/* 워프 높이를 위한 초기화 */
	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(size_t i = 0 ; i < pvecTile->size() ; ++i)
	{
		for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
		{
			if((*iterSys)->vSysPos.x == (*pvecTile)[i]->vTilePos.x
 				&& (*iterSys)->vSysPos.y == (*pvecTile)[i]->vTilePos.y)
			{
				 (*iterSys)->vSysPos.z = (*pvecTile)[i]->vTilePos.z;
			}
			if((*iterSys)->byDrawId == 7)
			{
				m_vOffset = (*iterSys)->vSysPos;
			}
		}
	}

	return S_OK;
}

SCENE CVillageWarp::Progress(void)
{
	return SCENE_NONPASS;
}

RECT CVillageWarp::GetWarpDraw(int _iDrawID)
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

void CVillageWarp::InitSysFromFile()
{
	for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
	{
		delete (*iterSys);
		(*iterSys) = NULL;
	}
	m_vecSys.clear();

	HANDLE	hFile;
	DWORD	dwByte;

	hFile = CreateFile( L"../Resource/Data/Village/Village_WARP.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	/* 워프 불러오기 */
	while(true)
	{
		SYSTEM*	pInfo = new SYSTEM;
		ReadFile(hFile,pInfo,sizeof(SYSTEM),&dwByte,NULL);
		if(dwByte == 0)
		{
			SAFE_DELETE(pInfo);
			break;
		}
		m_vecSys.push_back(pInfo);
	}

	CloseHandle(hFile);
}

void CVillageWarp::Render(void)
{			
	/* 워프 그리기 */
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
	if(pTexInfo == NULL)
		return ;

	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(vector<SYSTEM*>::iterator iterSys = m_vecSys.begin() ; iterSys != m_vecSys.end() ; ++iterSys)
	{
		if((*iterSys)->byDrawId != 7)
		{
			D3DXMatrixTranslation(&matWorld,(*iterSys)->vSysPos.x + m_vScroll.x,
				(*iterSys)->vSysPos.y + m_vScroll.y - 16 * (*iterSys)->vSysPos.z, 0.f);
			GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
			GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &GetWarpDraw((*iterSys)->byDrawId), 
				&D3DXVECTOR3((GetWarpDraw((*iterSys)->byDrawId).right - GetWarpDraw((*iterSys)->byDrawId).left) / 2.f, 
				float(GetWarpDraw((*iterSys)->byDrawId).bottom - GetWarpDraw((*iterSys)->byDrawId).top), 0.f),
				NULL,D3DCOLOR_ARGB(255,255,255,255));
		}
	}
}

void CVillageWarp::Release(void)
{
	for(size_t i = 0 ; i < m_vecSys.size() ; ++i)
	{
		SAFE_DELETE(m_vecSys[i]);
	}
	m_vecSys.clear();
}

CObj* CVillageWarp::Clone(void)
{
	return new CVillageWarp(*this);
}
