#include "StdAfx.h"
#include "VillageMouse.h"

#include "TextureMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

CVillageMouse::CVillageMouse(void)
{
}

CVillageMouse::CVillageMouse( const OBJ_INFO& _Info )
	:CVillageDynamic(_Info)
{
}

CVillageMouse::~CVillageMouse(void)
{
	Release();
}

HRESULT	CVillageMouse::Initialize(void)
{
	m_pObjKey = L"Mouse";
	m_fAngle = 0;
	m_fTime = 0;
	m_SortID = SORT_ID_MOUSE;
	
	m_Info.vPos = SetMouseInfo().vPos;

	return S_OK;
}

SCENE CVillageMouse::Progress(void)
{
	m_Info.vPos = SetMouseInfo().vPos;
	D3DXMATRIX matTrans, matScale;
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);

	if(PUSH_KEY(KEY_LBUTTON))
		D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 1.f);

	if(UP_KEY(KEY_LBUTTON))
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	m_Info.matWorld = matScale * matTrans;
	
	return SCENE_NONPASS;
}

RECT CVillageMouse::GetMouseDraw()
{
	RECT rcMouse;

	rcMouse.left = 156;
	rcMouse.top = 25;
	rcMouse.right = 197;
	rcMouse.bottom = 64;

	return rcMouse;
}


void CVillageMouse::Render(void)
{

	/* 마우스 커서 */
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
	if(pTexInfo == NULL)
		return ;

	m_Info.vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture,&GetMouseDraw(),
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255,255,255,255));
}

void CVillageMouse::Release(void)
{
}

CObj* CVillageMouse::Clone(void)
{
	return new CVillageMouse(*this);
}


