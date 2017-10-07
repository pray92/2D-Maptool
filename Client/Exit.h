#pragma once
#include "logostatic.h"
class CExit :
	public CLogoStatic
{
public:
	virtual HRESULT	Initialize();
	virtual SCENE Progress();
	virtual void Render();
	virtual void Release();
	virtual CObj* Clone();
public:
	CExit(void);
	CExit(const OBJ_INFO& _Info);
	~CExit(void);
};

