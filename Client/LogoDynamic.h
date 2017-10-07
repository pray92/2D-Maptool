#pragma once
#include "obj.h"
class CLogoDynamic :
	public CObj
{
protected:
	float m_fAngle;
	void Chase_Move(const OBJ_INFO& DestInfo);
public:
	virtual HRESULT	Initialize() PURE;
	virtual SCENE Progress() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual CObj* Clone() PURE;
public:
	CLogoDynamic(void);
	CLogoDynamic(const OBJ_INFO& _Info);
	virtual ~CLogoDynamic(void);
};

