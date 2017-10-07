#include "StdAfx.h"
#include "Logo.h"
#include "TextureMgr.h"

#include "LogoObjProto.h"
#include "ExitObjProto.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"

CLogo::CLogo(void)
{
}


CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::Initialize( void )
{

	m_pPrototype = new CLogoObjProto;
	if(FAILED(m_pPrototype->InitProtoInstance()))
	{
		ERR_MGS(g_hWnd, L"�ΰ� ������ Ÿ�� ���� ����");
		return E_FAIL;
	}

	/* Title �߰� */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Title");
	
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 255, 255, L"../Resource/Texture/Logo/Title.png",
		L"Title", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"Title Texture Load Failed");
		return E_FAIL;
	}
	
	/* Mouse �߰� */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Mouse");
	
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 29, 21, 17,L"../Resource/Texture/System/Mouse.png",
		L"Mouse", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"Mouse Texture Load Failed");
		return E_FAIL;
	}	
	
	/* Start �߰� */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Start");
	
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 0,L"../Resource/Texture/Logo/Button.png",
		L"Start", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"Start Texture Load Failed");
		return E_FAIL;
	}

	/* Load �߰� */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Load");
	
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 0,L"../Resource/Texture/Logo/Button.png",
		L"Load", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"Load Texture Load Failed");
		return E_FAIL;
	}

	/* End �߰� */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"End");
	
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 0,L"../Resource/Texture/Logo/Button.png",
		L"End", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"End Texture Load Failed");
		return E_FAIL;
	}
	
	//GET_SINGLE(CTimeMgr)->InitTimer();
	return S_OK;
}

void CLogo::Progress( void )
{
	//GET_SINGLE(CTimeMgr)->UpdateTimer();
	SCENE SceneID = GET_SINGLE(CObjMgr)->Progress();
	if(SceneID == SCENE_VILLAGE)
	{
		GET_SINGLE(CSceneMgr)->InitScene(SCENE_VILLAGE);
	}
}

void CLogo::Render( void )
{
	GET_SINGLE(CObjMgr)->Render();
}

void CLogo::Release( void )
{
	DESTROY_SINGLE(CObjMgr);
	DESTROY_SINGLE(CTextureMgr);
	SAFE_DELETE(m_pPrototype);
}