#include "StdAfx.h"
#include "VillageObject.h"

#include "TextureMgr.h"
#include "ObjMgr.h"

CVillageObject::CVillageObject(void)
{
}

CVillageObject::CVillageObject(const OBJ_INFO& _Info)
	:CVillageStatic(_Info)
{
}


CVillageObject::~CVillageObject()
{
	Release();
}

bool CompareObj(OBJECT* a, OBJECT* b)
{
	return (*a).vObjPos.y < (*b).vObjPos.y;
}

HRESULT	CVillageObject::Initialize()
{
	m_pObjKey = L"Object";
	m_SortID = SORT_ID_OBJECT;

	InitObjFromFile();
	
	/* 오브젝트 높이를 위한 초기화 */
	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(size_t i = 0 ; i < pvecTile->size() ; ++i)
	{
		for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
		{
			if((*iterObj)->vObjPos.x == (*pvecTile)[i]->vTilePos.x
 				&& (*iterObj)->vObjPos.y == (*pvecTile)[i]->vTilePos.y)
			{
				 (*iterObj)->vObjPos.z = (*pvecTile)[i]->vTilePos.z;
			}
		}
	}
	sort(m_vecObj.begin(), m_vecObj.end(), CompareObj);

	return S_OK;
}

SCENE CVillageObject::Progress()
{
	return SCENE_NONPASS;
}

RECT CVillageObject::GetObjDraw(int _iDrawID)
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

void CVillageObject::InitObjFromFile()
{
	for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin();
		iterObj != m_vecObj.end(); ++iterObj )
	{
		delete *iterObj;
		*iterObj = NULL;
	}
	m_vecObj.clear();	

	HANDLE hFile;
	DWORD dwByte;

	/* 오브젝트 불러오기 */
	hFile = CreateFile(L"../Resource/Data/Village/Village_OBJ.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		OBJECT*	pInfo = new OBJECT;
		ReadFile(hFile,pInfo,sizeof(OBJECT),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		m_vecObj.push_back(pInfo);
	}

	CloseHandle(hFile);
}

void CVillageObject::Render()
{
	/* 오브젝트 그리기 */
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
	if(pTexInfo == NULL)
		return ;

	const vector<TILE*>* pvecTile = GET_SINGLE(CObjMgr)->GetTileInfo();

	for(vector<OBJECT*>::iterator iterObj = m_vecObj.begin() ; iterObj != m_vecObj.end() ; ++iterObj)
	{
		D3DXMatrixTranslation(&matWorld,(*iterObj)->vObjPos.x + (int)m_vScroll.x,
			(*iterObj)->vObjPos.y + (int)m_vScroll.y - 16 * (*iterObj)->vObjPos.z, 0.f);
		GET_SINGLE(CDevice)->GetSprite()->SetTransform(&matWorld);
		GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &GetObjDraw((*iterObj)->byDrawId), 
			&D3DXVECTOR3((GetObjDraw((*iterObj)->byDrawId).right - GetObjDraw((*iterObj)->byDrawId).left) / 2.f, 
			float(GetObjDraw((*iterObj)->byDrawId).bottom - GetObjDraw((*iterObj)->byDrawId).top) - TILESIZEY / 2.f, 0.f),
			NULL,D3DCOLOR_ARGB(255,255,255,255));
	}
}

void CVillageObject::Release()
{
	for(size_t i = 0 ; i < m_vecObj.size() ; ++i)
	{
		SAFE_DELETE(m_vecObj[i]);
	}
	m_vecObj.clear();
}

CObj* CVillageObject::Clone()
{
	return new CVillageObject(*this);
}
