#pragma once
#include "villagedynamic.h"
class CVillagePlayer :
	public CVillageDynamic
{
private:
	PLAYER				m_Player;
	float				m_fTime;
	bool				m_bClicked;
	bool				m_bMoving;
private:
	void KeyCheck();
	void OnScroll();
	void Motion();
public:
	void InitPlayerFromFile();
public:
	RECT GetTileDraw(int _iIndex);
	RECT GetRootDraw(int _iIndex);
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CVillagePlayer(void);
	CVillagePlayer(const OBJ_INFO& _Info);
	~CVillagePlayer(void);
};

