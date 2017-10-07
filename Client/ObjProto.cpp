#include "StdAfx.h"
#include "ObjProto.h"


CObjProto::CObjProto(void)
{
}


CObjProto::~CObjProto(void)
{
	Release();
}

CObj*	CObjProto::GetProto(const TCHAR* pObjKey)
{
	map<const TCHAR*, CObj*>::iterator iter = m_MapProto.find(pObjKey);
	if(iter == m_MapProto.end())
		return NULL;

	return iter->second;
}

void CObjProto::Release()
{
	for(map<const TCHAR*, CObj*>::iterator iter = m_MapProto.begin() ;
		iter != m_MapProto.end() ; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_MapProto.clear();
}