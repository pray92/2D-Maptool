#include "StdAfx.h"
#include "LogoBack.h"
#include "TextureMgr.h"

CLogoBack::CLogoBack(void)
{
}


CLogoBack::~CLogoBack(void)
{
	Release();
}

CLogoBack::CLogoBack(const OBJ_INFO& _Info)
	:CLogoStatic(_Info)
{
}

HRESULT	CLogoBack::Initialize()
{
	m_pObjKey = L"LogoBack";
	m_pStateKey = NULL;
	m_SortID = SORT_ID_FIRST;

	return S_OK;
}

SCENE CLogoBack::Progress()
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	matWorld = matTrans;

	m_Info.matWorld = matWorld;

	return SCENE_NONPASS;
}

void CLogoBack::Render()
{
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);

	m_Info.vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255,255,255,255));
}

void CLogoBack::Release()
{
}

CObj* CLogoBack::Clone()
{
	return new CLogoBack(*this);
}