#pragma once
#include "logostatic.h"

class CLogoBack :
	public CLogoStatic
{
public:
	virtual HRESULT	Initialize();
	virtual SCENE Progress();
	virtual void Render();
	virtual void Release();
	virtual CObj* Clone();
public:
	CLogoBack(void);
	CLogoBack(const OBJ_INFO& _Info);
	~CLogoBack(void);
};

