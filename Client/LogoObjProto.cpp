#include "StdAfx.h"
#include "LogoObjProto.h"

#include "Title.h"
#include "Mouse.h"
#include "StartBtn.h"

CLogoObjProto::CLogoObjProto(void)
{
}


CLogoObjProto::~CLogoObjProto(void)
{
	Release();
}

HRESULT CLogoObjProto::InitProtoInstance()
{
	OBJ_INFO	ObjInfo;
	ZeroMemory(&ObjInfo, sizeof(OBJ_INFO));
	
	D3DXMatrixIdentity(&ObjInfo.matWorld);
	ObjInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	ObjInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	ObjInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_MapProto.insert(make_pair(L"Title", new CTitle(ObjInfo)));
	m_MapProto.insert(make_pair(L"Mouse", new CMouse(ObjInfo)));

	m_MapProto.insert(make_pair(L"Start", new CStartBtn(ObjInfo)));
	m_MapProto.insert(make_pair(L"Load", new CMouse(ObjInfo)));
	m_MapProto.insert(make_pair(L"End", new CMouse(ObjInfo)));
	//m_MapProto.insert(make_pair(L"Exit", new CCrossFire(ObjInfo)));
	
	return S_OK;
}