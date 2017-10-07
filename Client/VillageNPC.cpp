#include "StdAfx.h"
#include "VillageNPC.h"

#include "TextureMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

CVillageNPC::CVillageNPC(void)
{
}

CVillageNPC::CVillageNPC(const OBJ_INFO& _Info)
	:CVillageDynamic(_Info)
{
}

CVillageNPC::~CVillageNPC(void)
{
	Release();
}

void CVillageNPC::InitNPCFromFile()
{
	for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin();
		iterNPC != m_vecNPC.end(); ++iterNPC )
	{
		delete *iterNPC;
		*iterNPC = NULL;
	}
	m_vecNPC.clear();	

	HANDLE hFile;
	DWORD dwByte;

	/* 오브젝트 불러오기 */
	hFile = CreateFile(L"../Resource/Data/Village/Village_NPC.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		NPC*	pInfo = new NPC;
		ReadFile(hFile,pInfo,sizeof(NPC),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		m_vecNPC.push_back(pInfo);
	}

	CloseHandle(hFile);
}

bool CompareNPC(NPC* a, NPC* b)
{
	return (*a).tObjInfo.vPos.y < (*b).tObjInfo.vPos.y;
}

HRESULT	CVillageNPC::Initialize(void)
{
	m_SortID = SORT_ID_NPC;

	InitNPCFromFile();
		
	/* 오브젝트 높이를 위한 초기화 */
	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(size_t i = 0 ; i < pvecTile->size() ; ++i)
	{
		for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
		{
			if((*iterNPC)->tObjInfo.vPos.x == (*pvecTile)[i]->vTilePos.x
 				&& (*iterNPC)->tObjInfo.vPos.y == (*pvecTile)[i]->vTilePos.y)
			{
				 (*iterNPC)->tObjInfo.vPos.z = (*pvecTile)[i]->vTilePos.z;
			}
		}
	}
	sort(m_vecNPC.begin(), m_vecNPC.end(), CompareNPC);

	return S_OK;
}

SCENE CVillageNPC::Progress(void)
{
	return SCENE_NONPASS;
}

void CVillageNPC::Render(void)
{
	/* NPC 그리기 */
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Angel");
	if(pTexInfo == NULL)
		return ;

	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(vector<NPC*>::iterator iterNPC = m_vecNPC.begin() ; iterNPC != m_vecNPC.end() ; ++iterNPC)
	{
		RECT rc = {(*iterNPC)->iStartDir % 2 * 100, 0, rc.left + 100, 100};			
		switch((*iterNPC)->byDrawId)
		{
		case 1:
			//천사
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Angel");
			if(pTexInfo == NULL)
				continue;
			switch((*iterNPC)->iStartDir)
			{
			case 0:
			case 1:
				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y - 16 * (*iterNPC)->tObjInfo.vPos.z, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				break;
			case 2:
			case 3:
				D3DXMATRIX matScale;
				D3DXMatrixIdentity(&matScale);
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y - 16 *  (*iterNPC)->tObjInfo.vPos.z, 0.f);

				(*iterNPC)->tObjInfo.matWorld = matScale * (*iterNPC)->tObjInfo.matWorld;

				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				break;
			}
			break;
		case 2:
			//엘프
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Elf");
			if(pTexInfo == NULL)
				continue;
			switch((*iterNPC)->iStartDir)
			{
			case 0:
			case 1:
				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y - 16 *  (*iterNPC)->tObjInfo.vPos.z, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				break;
			case 2:
			case 3:
				D3DXMATRIX matScale;
				D3DXMatrixIdentity(&matScale);
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y - 16 *  (*iterNPC)->tObjInfo.vPos.z, 0.f);

				(*iterNPC)->tObjInfo.matWorld = matScale * (*iterNPC)->tObjInfo.matWorld;

				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				break;
			}
			break;
		case 3:
			//여성
			pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"Woman");
			if(pTexInfo == NULL)
				continue;
			switch((*iterNPC)->iStartDir)
			{
			case 0:
			case 1:
				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y  - 16 * (*iterNPC)->tObjInfo.vPos.z, 0.f);
				GET_SINGLE(CDevice)->GetSprite()->SetTransform(&(*iterNPC)->tObjInfo.matWorld);
				GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,
					&rc,&(*iterNPC)->tObjInfo.vCenter,NULL,D3DCOLOR_ARGB(255,255,255,255));
				break;
			case 2:
			case 3:
				D3DXMATRIX matScale;
				D3DXMatrixIdentity(&matScale);
				D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);

				D3DXMatrixTranslation(&(*iterNPC)->tObjInfo.matWorld, (*iterNPC)->tObjInfo.vPos.x + m_vScroll.x,
					(*iterNPC)->tObjInfo.vPos.y + m_vScroll.y - 16 *  (*iterNPC)->tObjInfo.vPos.z, 0.f);

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

void CVillageNPC::Release(void)
{
	for(size_t i = 0 ; i < m_vecNPC.size() ; ++i)
	{
		SAFE_DELETE(m_vecNPC[i]);
	}
	m_vecNPC.clear();
}

CObj* CVillageNPC::Clone(void)
{
	return new CVillageNPC(*this);
}