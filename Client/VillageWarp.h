#pragma once
#include "villagestatic.h"

class CVillageWarp :
	public CVillageStatic
{
private:
	vector<SYSTEM*>			m_vecSys;
	D3DXMATRIX				matWorld;
public:
	void InitSysFromFile();
	RECT GetWarpDraw(int _iDrawID);
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CVillageWarp(void);
	CVillageWarp(const OBJ_INFO& _Info);
	~CVillageWarp(void);
};

