#include "StdAfx.h"
#include "ExitObjProto.h"
#include "Exit.h"

CExitObjProto::CExitObjProto(void)
{
}


CExitObjProto::~CExitObjProto(void)
{
	Release();
}

HRESULT CExitObjProto::InitProtoInstance()
{
	OBJ_INFO	ObjInfo;
	ZeroMemory(&ObjInfo, sizeof(OBJ_INFO));

	D3DXMatrixIdentity(&ObjInfo.matWorld);
	ObjInfo.vPos = D3DXVECTOR3(1000.f,800.f,0.f);
	ObjInfo.vDir = D3DXVECTOR3(0.f,0.f,0.f);
	ObjInfo.vLook = D3DXVECTOR3(1.f,0.f,0.f);

	m_MapProto.insert(make_pair(L"Exit", new CExit(ObjInfo)));

	return S_OK;
}