#pragma once
#include "obj.h"

class CLogoStatic :
	public CObj
{
public:
	virtual HRESULT	Initialize() PURE;
	virtual SCENE Progress() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual CObj* Clone() PURE;
public:
	CLogoStatic(void);
	CLogoStatic(const OBJ_INFO& _Info);
	virtual ~CLogoStatic(void);
};

