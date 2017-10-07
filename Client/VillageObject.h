#pragma once
#include "villagestatic.h"

class CVillageObject :
	public CVillageStatic
{
private:
	vector<OBJECT*>			m_vecObj;
	D3DXMATRIX				matWorld;
public:
	void InitObjFromFile();
	RECT GetObjDraw(int _iDrawID);
public:
	const vector<OBJECT*>* GetObjInfo(){ return &m_vecObj; }
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CVillageObject(void);
	CVillageObject(const OBJ_INFO& _Info);
	~CVillageObject(void);
};

