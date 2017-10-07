#include "StdAfx.h"
#include "ObjMgr.h"

#include "ObjProto.h"
#include "SortMgr.h"

#include "VillageMap.h"
#include "VillageObject.h"

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

HRESULT	CObjMgr::AddObject(CPrototype* pProto,const TCHAR* pObjKey)
{
	CObj* pProtoInst = ((CObjProto*)pProto)->GetProto(pObjKey);

	if(pProtoInst == NULL)
		return E_FAIL;

	CObj* pObject = pProtoInst->Clone();
	pObject->Initialize();

	map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.find(pObjKey);
	if(iter == m_MapObject.end())
	{
		list<CObj*> ObjList;
		ObjList.push_back(pObject);
		m_MapObject.insert(make_pair(pObjKey, ObjList));
	}
	else
	{
		iter->second.push_back(pObject);
	}

	return S_OK;
}

SCENE CObjMgr::Progress(void)
{
	for(map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.begin() ;
		iter != m_MapObject.end() ; ++iter)
	{
		for(list<CObj*>::iterator iter2  = iter->second.begin() ; 
			iter2 != iter->second.end() ; ++iter2)
		{
			SCENE SceneID = (*iter2)->Progress();
			GET_SINGLE(CSortMgr)->AddSortObject(*iter2);
			if(SceneID > SCENE_NONPASS)
				return SceneID;
		}
	}

	return SCENE_NONPASS;
}

void CObjMgr::Render(void)
{
	//for(map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.begin() ;
	//	iter != m_MapObject.end() ; ++iter)
	//{
	//	for(list<CObj*>::iterator iter2  = iter->second.begin() ; 
	//		iter2 != iter->second.end() ; ++iter2)
	//	{
	//		(*iter2)->Render();
	//	}
	//}	

	GET_SINGLE(CSortMgr)->RenderSortObject();
}

void CObjMgr::Release(void)
{
	for(map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.begin() ;
		iter != m_MapObject.end() ; ++iter)
	{
		for(list<CObj*>::iterator iter2  = iter->second.begin() ; 
			iter2 != iter->second.end() ; ++iter2)
		{
			SAFE_DELETE(*iter2);
		}
		iter->second.clear();
	}
	m_MapObject.clear();

	GET_SINGLE(CSortMgr)->Release();
}

const vector<TILE*>* CObjMgr::GetTileInfo( void )
{
	map<const TCHAR*,list<CObj*>>::iterator iter = m_MapObject.find(L"Tile");

	if(iter == m_MapObject.end())
	{
		ERR_MGS(g_hWnd,L"타일 찾기 실패");
		return NULL;
	}

	return ((CVillageMap*)(iter->second.front()))->GetTileInfo();
}

const vector<TILE*>* CObjMgr::GetTmpInfo( void )
{
	map<const TCHAR*,list<CObj*>>::iterator iter = m_MapObject.find(L"Tile");

	if(iter == m_MapObject.end())
	{
		ERR_MGS(g_hWnd,L"타일 Tmp 찾기 실패");
		return NULL;
	}

	return ((CVillageMap*)(iter->second.front()))->GetTmpInfo();
}

const vector<OBJECT*>* CObjMgr::GetObjInfo()
{
	map<const TCHAR*,list<CObj*>>::iterator iter = m_MapObject.find(L"Object");

	if(iter == m_MapObject.end())
	{
		ERR_MGS(g_hWnd,L"오브젝트 찾기 실패");
		return NULL;
	}

	return ((CVillageObject*)(iter->second.front()))->GetObjInfo();
}