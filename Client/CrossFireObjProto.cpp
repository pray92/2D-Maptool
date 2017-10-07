#include "StdAfx.h"
#include "CrossFireObjProto.h"
#include "CrossFire.h"
#include "Exit.h"

CCrossFireObjProto::CCrossFireObjProto(void)
{
}


CCrossFireObjProto::~CCrossFireObjProto(void)
{
	Release();
}

HRESULT CCrossFireObjProto::InitProtoInstance()
{
	OBJ_INFO	ObjInfo;
	ZeroMemory(&ObjInfo, sizeof(OBJ_INFO));

	D3DXMatrixIdentity(&ObjInfo.matWorld);
	ObjInfo.vPos = D3DXVECTOR3(WINSIZEX / 2,WINSIZEY / 2,0.f);
	ObjInfo.vDir = D3DXVECTOR3(0.f,0.f,0.f);
	ObjInfo.vLook = D3DXVECTOR3(1.f,0.f,0.f);

	m_MapProto.insert(make_pair(L"HellFire", new CCrossFire(ObjInfo)));
	m_MapProto.insert(make_pair(L"Exit", new CExit(ObjInfo)));
	return S_OK;
}