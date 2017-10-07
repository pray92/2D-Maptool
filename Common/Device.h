#pragma once
#include "Define.h"
class CDevice
{
public:
	DECLARE_SINGLETON(CDevice);
private:
	//장치의 성능을 조사 , 디바이스 객체 생성
	LPDIRECT3D9		m_p3D;

	// 장치를 대표하는 객체
	LPDIRECT3DDEVICE9 m_pDevice;

	LPD3DXSPRITE	m_pSprite;
	//폰트 출력용 객체
	LPD3DXFONT		m_pFont;
	//라인 출력용 객체
	LPD3DXLINE		m_pLine;

public:
	LPD3DXSPRITE GetSprite(){ return m_pSprite; }
	LPDIRECT3DDEVICE9 GetDevice(){ return m_pDevice; }
	LPD3DXFONT GetFont(){ return m_pFont; }
	LPD3DXLINE GetLine(){ return m_pLine; }

	HRESULT	 InitDevice(HWND hWnd);
	void	 Release(void);
public:
	void	Render_Begin(void);
	void	Render_End(HWND _hwnd);
public:
	CDevice(void);
	~CDevice(void);
};

