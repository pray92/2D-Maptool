#include "StdAfx.h"
#include "VillageMap.h"

#include "TimeMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "VillagePlayer.h"

CVillageMap::CVillageMap(void)
{
}

CVillageMap::CVillageMap(const OBJ_INFO& _Info)
	:CVillageStatic(_Info)
{
}


CVillageMap::~CVillageMap(void)
{
	Release();
}

void CVillageMap::InitTileFromFile()
{
	for(vector<TILE*>::iterator iterTile = m_vecTile.begin() ; iterTile != m_vecTile.end() ; ++iterTile)
	{
		delete (*iterTile);
		(*iterTile) = NULL;
	}
	m_vecTile.clear();

	HANDLE	hFile;
	DWORD	dwByte;

	hFile = CreateFile(L"../Resource/Data/Village/Village.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);

	while(true)
	{
		TILE*	pInfo = new TILE;
		ReadFile(hFile,pInfo,sizeof(TILE),&dwByte,NULL);
		if(dwByte == 0)
		{
			SAFE_DELETE(pInfo);
			break;
		}
		m_vecTile.push_back(pInfo);
	}
	CloseHandle(hFile);
}

HRESULT	CVillageMap::Initialize(void)
{
	m_pObjKey = L"Tile";
	m_SortID = SORT_ID_TILE;

	rcMouse.left = 65;
	rcMouse.top = 0;
	rcMouse.right = 65 + TILESIZEX;
	rcMouse.bottom = TILESIZEY;

	InitTileFromFile();

	return S_OK;
}

SCENE CVillageMap::Progress(void)
{
	return SCENE_NONPASS;
}

RECT CVillageMap::GetTileDraw(int _iIndex)
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

RECT CVillageMap::GetRootDraw(int _iIndex)
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

bool CompareTile(TILE* a, TILE* b)
{
	return (*a).vTilePos.y > (*b).vTilePos.y;
}

void CVillageMap::Render(void)
{
	/* 타일 */
	m_vecTmp.clear();
	for (int i = 0; i < iShowTile * 4 ; ++i)
	{
		for (int j =0; j < iShowTile ; ++j)
		{
			int iIndex = (i - int(m_vScroll.y) / (TILESIZEY /2) ) * TILECNTX + (j - int(m_vScroll.x) / TILESIZEX);

			if(iIndex >= TILECNTX * TILECNTY || iIndex < 0)
				continue;

			const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
			if(pTexInfo == NULL)
				continue;
			//OBJ_INFO temp = CVillagePlayer::GetObjInfo();
			/* 타일 그리기 */
			for(int k = 0 ; k <= m_vecTile[iIndex]->vTilePos.z ; ++k)
			{
				D3DXMatrixTranslation(&matWorld,m_vecTile[iIndex]->vTilePos.x + (int)m_vScroll.x,
					(int)m_vecTile[iIndex]->vTilePos.y - 16 * k + (int)m_vScroll.y, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&GetTileDraw(iIndex),&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));

				/* 타일 인덱스 */
				//if(k == m_vecTile[iIndex]->vTilePos.z)
				//{
				//	TCHAR szTmp[128] = L"";	
				//	RECT	rcFont = {0};

				//	wsprintf(szTmp,L"%d", iIndex);		
				//	GET_SINGLE(CDevice)->GetFont()->DrawTextW(GET_SINGLE(CDevice)->GetSprite(),
				//		szTmp,lstrlen(szTmp),&rcFont,DT_NOCLIP,D3DCOLOR_ARGB(255,0,0,0));
				//}

				D3DXMatrixTranslation(&matWorld,m_vecTile[iIndex]->vRootPos.x + (int)m_vScroll.x,
					m_vecTile[iIndex]->vRootPos.y - 16 * k + (int)m_vScroll.y, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&GetRootDraw(iIndex),&D3DXVECTOR3(TILERTSIZEX / 2.f, TILERTSIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));
			}

			/* 마우스 타일 그리기 */
			D3DXVECTOR3 MouseTmp = SetMouseInfo().vPos;
			MouseTmp.y += m_vecTile[iIndex]->vTilePos.z * 16;
			if(CollsionMouseToTile(MouseTmp, m_vecTile[iIndex]))
			{
				m_vecTmp.push_back(m_vecTile[iIndex]);
			}
		}
	}
				
	sort(m_vecTmp.begin(), m_vecTmp.end(), CompareTile);
	
	if(!m_vecTmp.empty() && (*m_vecTmp.begin())->vTilePos.z >= 0)
	{
		const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"System");
		if(pTexInfo == NULL)
			return ;

		D3DXMatrixTranslation(&matWorld,(*m_vecTmp.begin())->vTilePos.x + m_vScroll.x,
			(*m_vecTmp.begin())->vTilePos.y - 16 * (*m_vecTmp.begin())->vTilePos.z + m_vScroll.y, 0.f);
		GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
		GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
			&rcMouse,&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f,0),NULL,D3DCOLOR_ARGB(255,255,255,255));		
	}
}

void CVillageMap::Release(void)
{
	for(size_t i = 0 ; i < m_vecTile.size() ; ++i)
	{
		delete m_vecTile[i];
		m_vecTile[i] = NULL;
	}
	m_vecTile.clear();

	for(size_t i = 0 ; i < m_vecTmp.size() ; ++i)
	{
		delete m_vecTmp[i];
		m_vecTmp[i] = NULL;
	}
	m_vecTmp.clear();
}

CObj* CVillageMap::Clone(void)
{
	return new CVillageMap(*this);
}