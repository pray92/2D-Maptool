#pragma once
#include "sceneobj.h"
#include "Define.h"

class CVillage :
	public CSceneObj
{
public:
	virtual HRESULT	Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	CVillage(void);
	~CVillage(void);
};

