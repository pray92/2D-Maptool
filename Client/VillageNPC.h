#pragma once
#include "villagedynamic.h"
class CVillageNPC :
	public CVillageDynamic
{
private:
	float			m_fTime;
	vector<NPC*>	m_vecNPC;
public:
	void InitNPCFromFile();
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CVillageNPC(void);
	CVillageNPC(const OBJ_INFO& _Info);
	~CVillageNPC(void);
};

