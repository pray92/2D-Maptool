#pragma once
#include "obj.h"
class CVillageDynamic :
	public CObj
{
protected:
	float m_fAngle;
protected:
	void Chase_Move(const OBJ_INFO& DestInfo);	
	void SetDirect(const OBJ_INFO& DestInfo);
	void AStar_Start(const D3DXVECTOR3& vDestPos, D3DXVECTOR3& vSourPos);
	void AStar_Move(void);
public:
	virtual HRESULT	Initialize() PURE;
	virtual SCENE Progress() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual CObj* Clone() PURE;
public:
	CVillageDynamic(void);
	CVillageDynamic(const OBJ_INFO& _Info);
	~CVillageDynamic(void);
};

