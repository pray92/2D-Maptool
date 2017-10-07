#include "StdAfx.h"
#include "MathMgr.h"

CMathMgr::CMathMgr(void)
{
}


CMathMgr::~CMathMgr(void)
{
}

bool CMathMgr::isBtnCollided(D3DXVECTOR3* const vMouse, OBJ_INFO* const pInfo, RECT* const rcBtn)
{
	if(pInfo->vPos.x + (*rcBtn).left <= (*vMouse).x && (*vMouse).x <= pInfo->vPos.x + (*rcBtn).right &&
		pInfo->vPos.y + (*rcBtn).top <= (*vMouse).y && (*vMouse).y <= pInfo->vPos.y + (*rcBtn).bottom )
		return true;
	return false;
}