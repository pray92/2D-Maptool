#pragma once
#include "objproto.h"
class CExitObjProto :
	public CObjProto
{
public:
	virtual HRESULT InitProtoInstance();
public:
	CExitObjProto(void);
	virtual ~CExitObjProto(void);
};

