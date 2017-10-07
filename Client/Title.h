#pragma once
#include "logostatic.h"

class CTitle :
	public CLogoStatic
{
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CTitle(void);
	CTitle(const OBJ_INFO& _Info);
	~CTitle(void);
};

