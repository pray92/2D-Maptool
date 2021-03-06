#include "StdAfx.h"
#include "Device.h"
#include "Define.h"

CDevice::CDevice(void)
	: m_p3D(NULL),m_pDevice(NULL),m_pSprite(NULL)
{
}


CDevice::~CDevice(void)
{
	Release();
}

HRESULT CDevice::InitDevice( HWND hWnd )
{
	//어플리케이션이 올바른 헤더로 만들어졌는지 확인
	m_p3D =  Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DCAPS9	devicecaps; //장치 설정을 빼오는 구조체
	ZeroMemory(&devicecaps,sizeof(D3DCAPS9));

	//D3DADAPTER_DEFAULT 그래픽카드 2개일때 주 그래픽을 뽑아옴,
	//D3DDEVTYPE_HAL 3D를 만들기 위한 버텍스처리를 그레픽 카드(하드웨어)에서 한다.

	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&devicecaps)))
	{
		ERR_MGS(hWnd,L"장치 정보 얻어오기 실패");
		return E_FAIL;
	}

	DWORD BehaviorFlag = 0;

	//DEVCAPS 하드웨어 지원여부 확인
	if(devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) //하드웨어 버텍스 프로세싱 지원 확인
	{
		BehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		BehaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	
	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //후면 버퍼 픽셀 포멧 결정

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	d3dpp.hDeviceWindow = hWnd; //내 윈도우 핸들
	d3dpp.Windowed = CUR_WINMODE; //전체 화면 여부

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //제일 빠름
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//1.D3DADAPTER_DEFAULT 위에서 쓴 DeviceCap이랑 동일하게
	//2.D3DDEVTYPE_HAL 디바이스 타입
	//3.부모 윈도우 핸들
	//4.버텍스 프로세싱 방법
	//5.세팅한 구조체
	//6.내 멤버 LPDIRECT3DDEVICE9 장치의 이중 포인터
	if(FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		BehaviorFlag,&d3dpp,&m_pDevice)))
	{
		ERR_MGS(hWnd,L"장치 생성 실패");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateSprite(m_pDevice,&m_pSprite)))
	{
		return E_FAIL;
	}

	/* 글자 및 글씨 초기화 */
	D3DXFONT_DESC	FontInfo;
	ZeroMemory(&FontInfo,sizeof(FontInfo));
	FontInfo.Height = 10;
	FontInfo.Width = 5;
	FontInfo.Weight = FW_HEAVY;
	FontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(FontInfo.FaceName,L"궁서");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice,&FontInfo,&m_pFont)))
	{
		ERR_MGS(hWnd,L"폰트 생성 실패");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateLine(m_pDevice,&m_pLine)))
	{
		ERR_MGS(hWnd,L"라인 생성 실패");
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::Release( void )
{
	m_pSprite->Release();
	m_pDevice->Release();
	m_p3D->Release();
}

void CDevice::Render_Begin( void )
{
	m_pDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255,0,0,0) /*0x0000FF00*/,1.0f,0);

	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CDevice::Render_End( HWND _hwnd )
{

	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL,NULL,_hwnd,NULL);
}
