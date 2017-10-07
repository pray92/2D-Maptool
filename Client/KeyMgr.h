#pragma once
class CKeyMgr
{
private:
	DWORD	m_dwKey;
public:
	DWORD GetKey() const { return m_dwKey; };
public:
	void CheckKey();
	DECLARE_SINGLETON(CKeyMgr);
public:
	CKeyMgr(void);
	~CKeyMgr(void);
};

