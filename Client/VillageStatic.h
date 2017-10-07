#pragma once
#include "obj.h"

class CVillageStatic :
	public CObj
{
public:
	virtual HRESULT	Initialize() PURE;
	virtual SCENE Progress() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual CObj* Clone() PURE;
public:
	CVillageStatic(void);
	CVillageStatic(const OBJ_INFO& _Info);
	~CVillageStatic(void);
};

