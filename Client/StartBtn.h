#pragma once
#include "logostatic.h"

class CStartBtn :
	public CLogoStatic
{
private:
	RECT m_rcBtn;
	int m_iFrame;
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CStartBtn(void);
	CStartBtn(const OBJ_INFO& _Info);
	~CStartBtn(void);
};

