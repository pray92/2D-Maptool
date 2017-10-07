#pragma once

class CObj;
class CSortMgr
{
public:
	DECLARE_SINGLETON(CSortMgr);
private:
	list<CObj*> m_ObjList[SORT_ID_END];
public:
	void AddSortObject(CObj* _pObj);
	void RenderSortObject();
	void Release();
private:
	CSortMgr(void);
public:
	~CSortMgr(void);
};
