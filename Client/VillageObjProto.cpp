#include "StdAfx.h"
#include "VillageObjProto.h"

#include "VillageMouse.h"
#include "VillageMap.h"
#include "VillageWarp.h"
#include "VillageObject.h"
#include "VillageNPC.h"
#include "VillagePlayer.h"

CVillageObjProto::CVillageObjProto(void)
{
}


CVillageObjProto::~CVillageObjProto(void)
{
	Release();
}

HRESULT CVillageObjProto::InitProtoInstance()
{
	OBJ_INFO	ObjInfo;
	ZeroMemory(&ObjInfo, sizeof(OBJ_INFO));

	D3DXMatrixIdentity(&ObjInfo.matWorld);
	ObjInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	ObjInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	ObjInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
	
	m_MapProto.insert(make_pair(L"Mouse", new CVillageMouse(ObjInfo)));
	m_MapProto.insert(make_pair(L"Tile", new CVillageMap(ObjInfo)));
	m_MapProto.insert(make_pair(L"Warp", new CVillageWarp(ObjInfo)));
	m_MapProto.insert(make_pair(L"Object", new CVillageObject(ObjInfo)));
	m_MapProto.insert(make_pair(L"Angel", new CVillageNPC(ObjInfo)));
	m_MapProto.insert(make_pair(L"Elf", new CVillageNPC(ObjInfo)));
	m_MapProto.insert(make_pair(L"Woman", new CVillageNPC(ObjInfo)));
	m_MapProto.insert(make_pair(L"Karin", new CVillagePlayer(ObjInfo)));

	return S_OK;
}