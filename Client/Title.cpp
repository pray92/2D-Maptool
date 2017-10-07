#include "StdAfx.h"
#include "Title.h"
#include "TextureMgr.h"

CTitle::CTitle(void)
{
}


CTitle::CTitle( const OBJ_INFO& _Info )
	:CLogoStatic(_Info)
{

}


CTitle::~CTitle(void)
{
	Release();
}

HRESULT	CTitle::Initialize()
{
	m_pObjKey = L"Title";
	m_pStateKey = NULL;
	m_SortID = SORT_ID_BACKGROUND;

	return S_OK;
}

SCENE CTitle::Progress()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x,
		m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matTrans;

	return SCENE_NONPASS;
}

void CTitle::Render()
{
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);

	if(pTexInfo == NULL)
		return ;

	m_Info.vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255,255,255));
}


void CTitle::Release()
{
}

CObj* CTitle::Clone()
{
	return new CTitle(*this);
}