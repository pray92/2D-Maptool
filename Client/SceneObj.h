#pragma once

#include "Define.h"
#include "Prototype.h"

class CSceneObj
{
protected:
	CPrototype* m_pPrototype;
public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
public:
	CSceneObj(void);
	virtual ~CSceneObj(void);
};

