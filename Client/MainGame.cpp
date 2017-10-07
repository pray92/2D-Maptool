#include "StdAfx.h"
#include "MainGame.h"

#include "Device.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

HRESULT	CMainGame::Initialize()
{	
	if(FAILED(GET_SINGLE(CDevice)->InitDevice(g_hWnd)))
	{
		ERR_MGS(g_hWnd,L"장치 초기화 실패");
		return E_FAIL;
	}

	if(FAILED(GET_SINGLE(CSceneMgr)->InitScene(SCENE_LOGO)))
	{
		ERR_MGS(g_hWnd,L"Scene 초기화 실패");
		return E_FAIL;
	}

	return S_OK;
}

void CMainGame::Progress()
{	
	GET_SINGLE(CKeyMgr)->CheckKey();
	GET_SINGLE(CSceneMgr)->Progress();
}

void CMainGame::Render()
{
	GET_SINGLE(CDevice)->Render_Begin();
	GET_SINGLE(CSceneMgr)->Render();
	GET_SINGLE(CDevice)->Render_End(g_hWnd);
}

void CMainGame::Release()
{
	DESTROY_SINGLE(CSceneMgr);
	DESTROY_SINGLE(CDevice);
}