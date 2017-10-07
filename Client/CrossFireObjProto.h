#pragma once
#include "objproto.h"

class CCrossFireObjProto :
	public CObjProto
{
public:
	virtual HRESULT InitProtoInstance();
public:
	CCrossFireObjProto(void);
	virtual ~CCrossFireObjProto(void);
};

