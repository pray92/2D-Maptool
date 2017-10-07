#pragma once
#include "villagedynamic.h"
class CVillageMouse :
	public CVillageDynamic
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
	CVillageMouse(void);
	CVillageMouse(const OBJ_INFO& _Info);
	~CVillageMouse(void);
};

