#pragma once

#include "Define.h"
class CTexture;

class CTextureMgr
{
public:
	DECLARE_SINGLETON(CTextureMgr);
private:
	map<const TCHAR*, CTexture*>	m_MapTexture;

public:
	const TEXINFO*	GetTexture(const TCHAR* pObjKey,
		const TCHAR* pStateKey = NULL, const int& iCnt =0);

	const HRESULT	InsertTexture(const int iAlpha, const int iRed,const int iGreen,const int iBlue, const TCHAR* pFileName,
		const TCHAR* pObjKey,TEXTTYPE TypeID,const TCHAR* pStateKey = NULL, const int& iCnt =0);

	void Release(void);

public:
	CTextureMgr(void);
	~CTextureMgr(void);
};

