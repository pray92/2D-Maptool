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
	//���ø����̼��� �ùٸ� ����� ����������� Ȯ��
	m_p3D =  Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DCAPS9	devicecaps; //��ġ ������ ������ ����ü
	ZeroMemory(&devicecaps,sizeof(D3DCAPS9));

	//D3DADAPTER_DEFAULT �׷���ī�� 2���϶� �� �׷����� �̾ƿ�,
	//D3DDEVTYPE_HAL 3D�� ����� ���� ���ؽ�ó���� �׷��� ī��(�ϵ����)���� �Ѵ�.

	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&devicecaps)))
	{
		ERR_MGS(hWnd,L"��ġ ���� ������ ����");
		return E_FAIL;
	}

	DWORD BehaviorFlag = 0;

	//DEVCAPS �ϵ���� �������� Ȯ��
	if(devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) //�ϵ���� ���ؽ� ���μ��� ���� Ȯ��
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
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //�ĸ� ���� �ȼ� ���� ����

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	d3dpp.hDeviceWindow = hWnd; //�� ������ �ڵ�
	d3dpp.Windowed = CUR_WINMODE; //��ü ȭ�� ����

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //���� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//1.D3DADAPTER_DEFAULT ������ �� DeviceCap�̶� �����ϰ�
	//2.D3DDEVTYPE_HAL ����̽� Ÿ��
	//3.�θ� ������ �ڵ�
	//4.���ؽ� ���μ��� ���
	//5.������ ����ü
	//6.�� ��� LPDIRECT3DDEVICE9 ��ġ�� ���� ������
	if(FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		BehaviorFlag,&d3dpp,&m_pDevice)))
	{
		ERR_MGS(hWnd,L"��ġ ���� ����");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateSprite(m_pDevice,&m_pSprite)))
	{
		return E_FAIL;
	}

	/* ���� �� �۾� �ʱ�ȭ */
	D3DXFONT_DESC	FontInfo;
	ZeroMemory(&FontInfo,sizeof(FontInfo));
	FontInfo.Height = 10;
	FontInfo.Width = 5;
	FontInfo.Weight = FW_HEAVY;
	FontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(FontInfo.FaceName,L"�ü�");

	if(FAILED(D3DXCreateFontIndirect(m_pDevice,&FontInfo,&m_pFont)))
	{
		ERR_MGS(hWnd,L"��Ʈ ���� ����");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateLine(m_pDevice,&m_pLine)))
	{
		ERR_MGS(hWnd,L"���� ���� ����");
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
