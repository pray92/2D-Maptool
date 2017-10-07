#pragma once
#include "logodynamic.h"
class CMouse :
	public CLogoDynamic
{
private:
	float m_fTime;
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	RECT GetMouseDraw();
public:
	CMouse(void);
	CMouse( const OBJ_INFO& _Info );
	~CMouse(void);
};

