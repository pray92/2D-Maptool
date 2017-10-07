#pragma once

#include "Define.h"

class CSceneObj;
class CSceneMgr
{
public:
	DECLARE_SINGLETON(CSceneMgr);
private:
	CSceneObj* m_pSceneObj;
public:
	HRESULT	InitScene(SCENE _Scene);
	void Progress(void);
	void Render(void);
	void Release(void);
public:
	CSceneMgr(void);
	~CSceneMgr(void);
};

