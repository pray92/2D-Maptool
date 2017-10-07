#include "StdAfx.h"
#include "CrossFire.h"

#include "TextureMgr.h"
#include "TimeMgr.h"

CCrossFire::CCrossFire(void)
{
}

CCrossFire::~CCrossFire(void)
{
	Release();
}

CCrossFire::CCrossFire(const OBJ_INFO& _Info)
	:CLogoDynamic(_Info)
{
}

HRESULT	CCrossFire::Initialize()
{
	m_pObjKey = L"HellFire";
	m_pStateKey = NULL;
	m_fAngle = 0.f;
	m_SortID = SORT_ID_LAST;

	return S_OK;
}

SCENE CCrossFire::Progress()
{
	MouseInfo = GetMouseInfo();
	Chase_Move(MouseInfo);

	m_fAngle += D3DXToRadian(90.f * GET_SINGLE(CTimeMgr)->GetTime());
	//GET_SINGLE(CTimeMgr)->GetTime();

	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRotZ;

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	matWorld = matRotZ * matTrans;

 	m_Info.matWorld = matWorld;

	return SCENE_NONPASS;
}

void CCrossFire::Render()
{
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);

	m_Info.vCenter = D3DXVECTOR3( pTexInfo->ImgInfo.Width / 2, pTexInfo->ImgInfo.Height / 2, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB( 255, 255, 255, 255));
}
 
void CCrossFire::Release()
{
}

CObj* CCrossFire::Clone()
{
	return new CCrossFire(*this);
}

const OBJ_INFO CCrossFire::GetMouseInfo()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	OBJ_INFO FireInfo;
	ZeroMemory(&FireInfo, sizeof(OBJ_INFO));

	FireInfo.vPos = D3DXVECTOR3(float(ptMouse.x), float(ptMouse.y), 0);

	return FireInfo;
}
