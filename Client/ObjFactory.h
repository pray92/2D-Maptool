#pragma once

class CObj;
template<typename T>
class CObjFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		//pObj->SetPos(_fX, _fY);
		return pObj;
	}
public:
	CObjFactory();
	~CObjFactory();
};