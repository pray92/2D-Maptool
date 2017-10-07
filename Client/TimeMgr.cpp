#include "StdAfx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr(void)
{
}


CTimeMgr::~CTimeMgr(void)
{
}

void CTimeMgr::InitTimer()
{
	/* CPU Ÿ�̸� �������� */
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CPUTick);
}

void CTimeMgr::UpdateTimer()
{

	QueryPerformanceCounter(&m_FrameTime);
	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CPUTick.QuadPart)
	{
		/* 1�ʵ��� ������ CPU �� �������� */
		QueryPerformanceFrequency(&m_CPUTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CPUTick.QuadPart;
	m_FixTime = m_FrameTime;
}