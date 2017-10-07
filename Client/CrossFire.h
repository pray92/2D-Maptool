#pragma once
#include "logodynamic.h"
class CCrossFire :
	public CLogoDynamic
{
private:
	OBJ_INFO MouseInfo;
	const OBJ_INFO GetMouseInfo();
public:
	virtual HRESULT	Initialize();
	virtual SCENE Progress();
	virtual void Render();
	virtual void Release();
	virtual CObj* Clone();
public:
	CCrossFire(void);
	CCrossFire(const OBJ_INFO& _Info);
	virtual ~CCrossFire(void);
};

