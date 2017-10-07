#pragma once

class CObj;
class CPrototype;
class CObjMgr
{
public:
	DECLARE_SINGLETON(CObjMgr);
private:
	map<const TCHAR*, list<CObj*>> m_MapObject;
public:
	HRESULT	AddObject(CPrototype* pProto,const TCHAR* pObjKey);
	SCENE Progress(void);
	void Render(void);
	void Release(void);
public:
	const vector<TILE*>* GetTileInfo();
	const vector<TILE*>* GetTmpInfo();
	const vector<OBJECT*>* GetObjInfo();
public:
	CObjMgr(void);
	~CObjMgr(void);
};

