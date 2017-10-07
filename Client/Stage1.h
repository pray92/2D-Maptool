#pragma once
#include "sceneobj.h"
class CStage1 :
	public CSceneObj
{
protected:
	
public:
	virtual HRESULT	Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStage1(void);
	virtual ~CStage1(void);
};

