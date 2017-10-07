#pragma once
#include "prototype.h"
#include "Obj.h"

class CObjProto :
	public CPrototype
{
protected:
	map<const TCHAR*, CObj*>	m_MapProto;
public:
	CObj*	GetProto(const TCHAR* pObjKey);
	virtual HRESULT InitProtoInstance() PURE;
	virtual void Release();
public:
	CObjProto(void);
	virtual ~CObjProto(void);
};

