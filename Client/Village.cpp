#include "StdAfx.h"
#include "Village.h"

#include "TextureMgr.h"
#include "VillageObjProto.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"

CVillage::CVillage(void)
{
}


CVillage::~CVillage(void)
{
	Release();
}

HRESULT	CVillage::Initialize()
{
	m_pPrototype = new CVillageObjProto;
	if(FAILED(m_pPrototype->InitProtoInstance()))
	{
		ERR_MGS(g_hWnd, L"마을 프로토 타입 생성 실패");
		return E_FAIL;
	}
	
	/* 타일 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Tile");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 255, L"../Resource/Texture/Map/MapEx.png",L"Tile",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Tile Texture Load Failed");
		return E_FAIL;
	}

	/* 오브젝트 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Object");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 0, 255, L"../Resource/Texture/Map/MapEx.png",L"Object",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Object Texture Load Failed");
		return E_FAIL;
	}
	
	/* 마우스 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Mouse");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 29, 21, 17,L"../Resource/Texture/System/Mouse.png",
		L"Mouse", TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd,L"Mouse Texture Load Failed");
		return E_FAIL;
	}	
	/* 마우스 타일 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"System");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 0, L"../Resource/Texture/System/System.png",L"System",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Mouse Tile Texture Load Failed");
		return E_FAIL;
	}
	
	/* 워프 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Warp");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 128, 0, 128, L"../Resource/Texture/System/Wall.png",L"Warp",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Warp Texture Load Failed");
		return E_FAIL;
	}
	
	/* 고블린 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Goblin");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Goblin.png",L"Goblin",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Goblin Texture Load Failed");
		return E_FAIL;
	}
	
	/* 슬라임 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Slime");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Slime.png",L"Slime",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Slime Texture Load Failed");
		return E_FAIL;
	}

	/* 타락천사 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Boss");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/Monster/Boss/Boss%d.png",L"Boss",
		TEXTTYPE_MULTI, L"Monster", 19)))
	{
		ERR_MGS(g_hWnd, L"Boss Texture Load Failed");
		return E_FAIL;
	}
		
	/* 천사 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Angel");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Angel.png",L"Angel",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Angel Texture Load Failed");
		return E_FAIL;
	}	

	/* 엘프 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Elf");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Elf.png",L"Elf",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Elf Texture Load Failed");
		return E_FAIL;
	}	

	/* 여자 */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Woman");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 255, 0, 255, L"../Resource/Texture/NPC/Woman.png",L"Woman",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Woman Texture Load Failed");
		return E_FAIL;
	}

	/* 플레이어(카린) */
	GET_SINGLE(CObjMgr)->AddObject(m_pPrototype,L"Karin");
	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(255, 0, 255, 255, L"../Resource/Texture/Player/Karin.png",L"Karin",
		TEXTTYPE_SINGLE)))
	{
		ERR_MGS(g_hWnd, L"Karin Texture Load Failed");
		return E_FAIL;
	}

	GET_SINGLE(CTimeMgr)->InitTimer();

	return S_OK;
}

void CVillage::Progress()
{	
	GET_SINGLE(CTimeMgr)->UpdateTimer();
	SCENE SceneID =  GET_SINGLE(CObjMgr)->Progress();

	if(SceneID == SCENE_VILLAGE)
	{
		if(FAILED(GET_SINGLE(CSceneMgr)->InitScene(SCENE_VILLAGE)))
		{
			ERR_MGS(g_hWnd,L"씬 초기화 실패");
		}
	}
}

void CVillage::Render()
{
	GET_SINGLE(CObjMgr)->Render();
}

void CVillage::Release()
{
	DESTROY_SINGLE(CObjMgr);
	DESTROY_SINGLE(CTextureMgr);
	SAFE_DELETE(m_pPrototype);
}
