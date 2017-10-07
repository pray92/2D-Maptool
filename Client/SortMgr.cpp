#include "StdAfx.h"
#include "SortMgr.h"
#include "Obj.h"

CSortMgr::CSortMgr(void)
{
}

CSortMgr::~CSortMgr(void)
{
	Release();
}

void CSortMgr::AddSortObject(CObj* _pObj)
{
	m_ObjList[_pObj->GetSortID()].push_back(_pObj);
}

void CSortMgr::RenderSortObject()
{
	for(int i = 0 ; i < SORT_ID_END ; ++i)
	{
		for(list<CObj*>::iterator iter = m_ObjList[i].begin() ; 
			iter != m_ObjList[i].end() ; ++iter)
		{
			(*iter)->Render();
		}
		m_ObjList[i].clear();
	}
}

void CSortMgr::Release()
{
	for(int i = 0 ; i < SORT_ID_END ; ++i)
	{
		m_ObjList[i].clear();
	}
}