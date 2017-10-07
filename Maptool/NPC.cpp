// NPC.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Maptool.h"
#include "NPC.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MaptoolView.h"


// CNPC ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNPC, CPropertyPage)

CNPC::CNPC()
	: CPropertyPage(CNPC::IDD)
{

}

CNPC::~CNPC()
{
}

void CNPC::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CNPC, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNPC::OnCbnSelchangeCombo1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO1, &CNPC::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CNPC::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CNPC::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CNPC::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CNPC::OnBnClickedRadio5)
END_MESSAGE_MAP()


// CNPC �޽��� ó�����Դϴ�.

/* �޺� �ڽ� */
void CNPC::OnCbnSelchangeCombo1()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CString		str = L"";
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Combo.GetLBText(m_Combo.GetCurSel(), str);

	pMainFrm->m_pMainView->m_iSelectTileID = -1;
	pMainFrm->m_pMainView->m_iSelectObjID = -1;
	pMainFrm->m_pMainView->m_iSelectWarpID = -1;
	pMainFrm->m_pMainView->m_iSelectMonsterID = -1;
	if(str == L"õ��")
	{
		m_Picture.SetBitmap(m_Bitmap[0]);
		pMainFrm->m_pMainView->m_iSelectNPCID = 1;
	}
	else if(str == L"����")
	{
		m_Picture.SetBitmap(m_Bitmap[1]);
		pMainFrm->m_pMainView->m_iSelectNPCID = 2;
	}
	else
	{
		m_Picture.SetBitmap(m_Bitmap[2]);
		pMainFrm->m_pMainView->m_iSelectNPCID = 3;
	}

	str.ReleaseBuffer();
}

void CNPC::OnDestroy()
{	
	CPropertyPage::OnDestroy();
	for(int i = 0 ; i < NPC_CNT ; ++i)
	{
		DeleteObject(m_Bitmap[i]);
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CNPC::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	TCHAR szTmp[128] = L"";
	RECT rcPicture = { 0, 0, 100, 100};

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Combo.InsertString(0, L"õ��");
	m_Combo.InsertString(1, L"����");
	m_Combo.InsertString(2, L"����");

	m_Picture.GetWindowRect(&rcPicture);
	SetRect(&rcPicture, 0, 0, rcPicture.right - rcPicture.left, rcPicture.bottom - rcPicture.top);
	
	m_Bitmap[0] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/NPC/Angel.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Bitmap[1] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/NPC/Elf.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Bitmap[2] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/NPC/Woman.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

/* ��ȭ */
void CNPC::OnBnClickedRadio1()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pMainFrm->m_pMainView->m_NPCClass = MERCHANDISE_CLASS;
}

/* ���� */
void CNPC::OnBnClickedRadio2()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pMainFrm->m_pMainView->m_NPCClass = SMITH_CLASS;
}

/* ����Ʈ1 */
void CNPC::OnBnClickedRadio3()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pMainFrm->m_pMainView->m_NPCClass = QUEST1_CLASS;
}

/* ����Ʈ2 */
void CNPC::OnBnClickedRadio4()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pMainFrm->m_pMainView->m_NPCClass = QUEST2_CLASS;
}

/* ��Ÿ */
void CNPC::OnBnClickedRadio5()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pMainFrm->m_pMainView->m_NPCClass = ETC_CLASS;
}
