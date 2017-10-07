#pragma once

class CMathMgr
{
public:
	DECLARE_SINGLETON(CMathMgr);
public:
	static bool isBtnCollided(D3DXVECTOR3* const vMouse, OBJ_INFO* const pInfo, RECT* const rcBtn);
public:
	CMathMgr(void);
	~CMathMgr(void);
};

