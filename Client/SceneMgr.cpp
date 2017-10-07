#include "StdAfx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "Village.h"
#include "Stage1.h"

CSceneMgr::CSceneMgr(void)
	:m_pSceneObj(NULL)
{
}


CSceneMgr::~CSceneMgr(void)
{
	Release();
}


HRESULT	CSceneMgr::InitScene(SCENE _Scene)
{
	SAFE_DELETE(m_pSceneObj);

	switch(_Scene)
	{
	case SCENE_LOGO:
		m_pSceneObj = new CLogo;
		break;
	case SCENE_VILLAGE:
		m_pSceneObj = new CVillage;
		break;
	}

	if(FAILED(m_pSceneObj->Initialize()))
	{
		SAFE_DELETE(m_pSceneObj);
		return E_FAIL;
	}

	return S_OK;
}

void CSceneMgr::Progress(void)
{
	m_pSceneObj->Progress();
}

void CSceneMgr::Render(void)
{
	m_pSceneObj->Render();
}

void CSceneMgr::Release(void)
{
	SAFE_DELETE(m_pSceneObj);
}