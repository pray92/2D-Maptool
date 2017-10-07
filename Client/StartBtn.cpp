#include "StdAfx.h"
#include "StartBtn.h"
#include "TextureMgr.h"
#include "MathMgr.h"

CStartBtn::CStartBtn(void)
{
}


CStartBtn::CStartBtn( const OBJ_INFO& _Info )
	:CLogoStatic(_Info)
{

}


CStartBtn::~CStartBtn(void)
{
	Release();
}

HRESULT	CStartBtn::Initialize()
{
	m_pObjKey = L"Start";
	m_pStateKey = NULL;
	m_SortID = SORT_ID_BUTTON;
	m_iFrame = 0;
	m_Info.vPos = D3DXVECTOR3(100.f, 530.f, 0.f);

	return S_OK;
}

SCENE CStartBtn::Progress()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matTrans;

	D3DXVECTOR3 vMouse = SetMouseInfo().vPos;
	if(GET_SINGLE(CMathMgr)->isBtnCollided(&vMouse, &m_Info, &m_rcBtn))
		m_iFrame = 1;
	else
		m_iFrame = 0;
	
	return SCENE_VILLAGE;		//무조건 빌리지 이동
	//return SCENE_NONPASS;
}

void CStartBtn::Render()
{
	const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);

	if(pTexInfo == NULL)
		return ;

	/* 버튼 활성 / 비활성화 */
	m_rcBtn.left = m_iFrame * 163;
	m_rcBtn.top = 0;
	m_rcBtn.right = m_iFrame * 163 + 162;
	m_rcBtn.bottom = 50;

	m_Info.vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
	GET_SINGLE(CDevice)->GetSprite()->Draw(pTexInfo->pTexture, &m_rcBtn,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CStartBtn::Release()
{
}

CObj* CStartBtn::Clone()
{
	return new CStartBtn(*this);
}