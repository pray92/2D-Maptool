#include "StdAfx.h"
#include "TextureMgr.h"
#include "MultiTexture.h"
#include "SingleTexture.h"


CTextureMgr::CTextureMgr(void)
{
}


CTextureMgr::~CTextureMgr(void)
{
	Release();
}

const HRESULT CTextureMgr::InsertTexture(const int iAlpha, const int iRed,const int iGreen,const int iBlue, const TCHAR* pFileName, const TCHAR* pObjKey,TEXTTYPE TypeID,const TCHAR* pStateKey, const int& iCnt /*=0*/)
{
	map<const TCHAR*, CTexture*>::iterator iter = m_MapTexture.find(pObjKey);

	if(iter == m_MapTexture.end())
	{
		CTexture*	pTexture = NULL;
		switch(TypeID)
		{
		case TEXTTYPE_SINGLE:
			pTexture = new CSingleTexture();
			break;
		case TEXTTYPE_MULTI:
			pTexture = new CMultiTexture();
			break;
		}

		if(FAILED(pTexture->InsertTexture(iAlpha, iRed, iGreen, iBlue, pFileName,pStateKey,iCnt)))
			return E_FAIL;

		m_MapTexture.insert(make_pair(pObjKey,pTexture));
	}
	else
		return E_FAIL;

	return S_OK;
}

const TEXINFO* CTextureMgr::GetTexture( const TCHAR* pObjKey, const TCHAR* pStateKey /*= NULL*/, const int& iCnt /*=0*/ )
{
	map<const TCHAR*, CTexture*>::iterator iter = m_MapTexture.find(pObjKey);

	if(iter == m_MapTexture.end()){
		return NULL;
	}

	return iter->second->GetTexture(pStateKey,iCnt);
}

void CTextureMgr::Release(void)
{
	for(map<const TCHAR*, CTexture*>::iterator iter = m_MapTexture.begin();
		iter != m_MapTexture.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}
	m_MapTexture.clear();
}