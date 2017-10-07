#include "StdAfx.h"
#include "MultiTexture.h"
#include "Device.h"


CMultiTexture::CMultiTexture(void)
{
}


CMultiTexture::~CMultiTexture(void)
{
	Release();
}

const TEXINFO* CMultiTexture::GetTexture( const TCHAR* pStateKey /*= NULL*/,const int& iCnt /*=0*/ )
{
	map<const TCHAR*,vector<TEXINFO*>>::iterator iter = m_pMapTexture.find(pStateKey);

	if(iter == m_pMapTexture.end())
		return NULL;

	return iter->second[iCnt];
}

const HRESULT CMultiTexture::InsertTexture(const int iAlpha, const int iRed,const int iGreen,const int iBlue, const TCHAR* pFileName,const TCHAR* pStateKey /*= NULL*/,const int& iCnt /*=0*/)
{
	TCHAR	szPath[128] = L"";
	vector<TEXINFO*>	vecTexture;

	for(int i = 0 ; i < iCnt; ++i)
	{
		wsprintf(szPath,pFileName,i);
		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo,sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath,&pTexInfo->ImgInfo)))
		{
			return E_FAIL;
		}

		if(FAILED(D3DXCreateTextureFromFileEx(GET_SINGLE(CDevice)->GetDevice(),
			szPath,
			pTexInfo->ImgInfo.Width,pTexInfo->ImgInfo.Height,
			pTexInfo->ImgInfo.MipLevels,0, pTexInfo->ImgInfo.Format,D3DPOOL_MANAGED, D3DX_DEFAULT,D3DX_DEFAULT,
			D3DCOLOR_ARGB(iAlpha,iRed,iGreen,iBlue),
			&pTexInfo->ImgInfo, NULL,&pTexInfo->pTexture)))
		{
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);

	}


	m_pMapTexture.insert(make_pair(pStateKey,vecTexture));
	return S_OK;
}

void CMultiTexture::Release( void )
{
	
	for(map<const TCHAR*,vector<TEXINFO*>>::iterator iter = m_pMapTexture.begin();
		iter != m_pMapTexture.end(); ++iter)
	{
		for (size_t i=0; i< iter->second.size();++i )
		{
			iter->second[i]->pTexture->Release();
			delete iter->second[i];
			iter->second[i] = NULL;
		}
		iter->second.clear();
	}

	m_pMapTexture.clear();
}
