#pragma once
class CTimeMgr
{
public:
	DECLARE_SINGLETON(CTimeMgr);
private:
	LARGE_INTEGER	m_FrameTime;
	LARGE_INTEGER	m_FixTime;
	LARGE_INTEGER	m_LastTime;
	LARGE_INTEGER	m_CPUTick;
	float			m_fTime;
public:
	void InitTimer();
	void UpdateTimer();
public:
	float GetTime() const{ return m_fTime; }
private:
	CTimeMgr(void);
public:
	~CTimeMgr(void);
};

