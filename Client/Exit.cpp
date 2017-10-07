#include "StdAfx.h"
#include "Exit.h"
#include "TextureMgr.h"

CExit::CExit(void)
{
}


CExit::~CExit(void)
{
}

CExit::CExit(const OBJ_INFO& _Info)
	:CLogoStatic(_Info)
{
}

HRESULT	CExit::Initialize()
{
	m_pObjKey = L"Exit";
	m_pStateKey = NULL;

	return S_OK;
}

SCENE CExit::Progress()
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	matWorld = matTrans;

	m_Info.matWorld = matWorld;

	return SCENE_NONPASS;
}

void CExit::Render()
{
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
	
 	m_Info.vCenter = D3DXVECTOR3( 80.5f, 39.5f, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255,255,255,255));
}

void CExit::Release()
{
}

CObj* CExit::Clone()
{
	return new CExit(*this);
}