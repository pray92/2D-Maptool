#pragma once
#include "Define.h"
class CTexture
{
public:
	virtual const TEXINFO*	GetTexture(const TCHAR* pStateKey = NULL,const int& iCnt =0) PURE;
public:
	virtual const HRESULT	InsertTexture(const int iAlpha, const int iRed,const int iGreen,const int iBlue,const TCHAR* pFileName,const TCHAR* pStateKey = NULL,const int& iCnt =0) PURE;
	virtual void Release(void)PURE;
public:
	CTexture(void);
	virtual ~CTexture(void);
};

