#include "StdAfx.h"
#include "LogoDynamic.h"


CLogoDynamic::CLogoDynamic(void)
{
}


CLogoDynamic::~CLogoDynamic(void)
{
}

CLogoDynamic::CLogoDynamic(const OBJ_INFO& _Info)
	:CObj(_Info)
{
}

void CLogoDynamic::Chase_Move(const OBJ_INFO& DestInfo)
{
	m_Info.vDir = DestInfo.vPos - m_Info.vPos;
	float fDistance = D3DXVec3LengthSq(&m_Info.vDir);

	if(fDistance > 10)
	{
		D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
		m_Info.vPos += m_Info.vDir * 10.f;
	}
}