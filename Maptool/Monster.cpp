// Monster.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Maptool.h"
#include "Monster.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MaptoolView.h"

// CMonster 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonster, CPropertyPage)

CMonster::CMonster()
	: CPropertyPage(CMonster::IDD)
	, m_Atk(_T(""))
	, m_HP(_T(""))
	, m_MP(_T(""))
	, m_Def(_T(""))
	, m_Exp(_T(""))
	, m_Money(_T(""))
{

}

CMonster::~CMonster()
{
}

void CMonster::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT1, m_Atk);
	DDX_Text(pDX, IDC_EDIT3, m_HP);
	DDX_Text(pDX, IDC_EDIT4, m_MP);
	DDX_Text(pDX, IDC_EDIT7, m_Def);
	DDX_Text(pDX, IDC_EDIT5, m_Exp);
	DDX_Text(pDX, IDC_EDIT6, m_Money);
}

BEGIN_MESSAGE_MAP(CMonster, CPropertyPage)
	ON_BN_CLICKED(IDC_RADIO4, &CMonster::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO2, &CMonster::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMonster::OnBnClickedRadio3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMonster::OnCbnSelchangeCombo1)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT1, &CMonster::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CMonster::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMonster::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT7, &CMonster::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT5, &CMonster::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMonster::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CMonster 메시지 처리기입니다.

/* 마법 계열 */
void CMonster::OnBnClickedRadio4()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_MonsterClass = MAGICAL_CLASS;

	pMainFrm->m_pMainView->m_iLevel = 1;
	SetDlgItemInt(IDC_EDIT1, 10);
	pMainFrm->m_pMainView->m_iAttack = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemInt(IDC_EDIT3, 50);
	pMainFrm->m_pMainView->m_iHP = GetDlgItemInt(IDC_EDIT3);
	SetDlgItemInt(IDC_EDIT4, 100);
	pMainFrm->m_pMainView->m_iMP =  GetDlgItemInt(IDC_EDIT4);
	SetDlgItemInt(IDC_EDIT7, 5);
	pMainFrm->m_pMainView->m_iDefence =  GetDlgItemInt(IDC_EDIT7);
	SetDlgItemInt(IDC_EDIT5, 40);
	pMainFrm->m_pMainView->m_iExp =  GetDlgItemInt(IDC_EDIT5);
	SetDlgItemInt(IDC_EDIT6, 50);
	pMainFrm->m_pMainView->m_iMoney =  GetDlgItemInt(IDC_EDIT6);	
}

/* 근접 계열 */
void CMonster::OnBnClickedRadio2()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_MonsterClass = PHYSICAL_CLASS;

	pMainFrm->m_pMainView->m_iLevel = 1;
	SetDlgItemInt(IDC_EDIT1, 5);
	pMainFrm->m_pMainView->m_iAttack = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemInt(IDC_EDIT3, 100);
	pMainFrm->m_pMainView->m_iHP = GetDlgItemInt(IDC_EDIT3);
	SetDlgItemInt(IDC_EDIT4, 10);
	pMainFrm->m_pMainView->m_iMP =  GetDlgItemInt(IDC_EDIT4);
	SetDlgItemInt(IDC_EDIT7, 10);
	pMainFrm->m_pMainView->m_iDefence =  GetDlgItemInt(IDC_EDIT7);
	SetDlgItemInt(IDC_EDIT5, 40);
	pMainFrm->m_pMainView->m_iExp =  GetDlgItemInt(IDC_EDIT5);
	SetDlgItemInt(IDC_EDIT6, 50);
	pMainFrm->m_pMainView->m_iMoney =  GetDlgItemInt(IDC_EDIT6);
}

/* 보스 */
void CMonster::OnBnClickedRadio3()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_MonsterClass = BOSS_CLASS;

	pMainFrm->m_pMainView->m_iLevel = 1;
	SetDlgItemInt(IDC_EDIT1, 20);
	pMainFrm->m_pMainView->m_iAttack = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemInt(IDC_EDIT3, 300);
	pMainFrm->m_pMainView->m_iHP = GetDlgItemInt(IDC_EDIT3);
	SetDlgItemInt(IDC_EDIT4, 100);
	pMainFrm->m_pMainView->m_iMP =  GetDlgItemInt(IDC_EDIT4);
	SetDlgItemInt(IDC_EDIT7, 15);
	pMainFrm->m_pMainView->m_iDefence =  GetDlgItemInt(IDC_EDIT7);
	SetDlgItemInt(IDC_EDIT5, 500);
	pMainFrm->m_pMainView->m_iExp =  GetDlgItemInt(IDC_EDIT5);
	SetDlgItemInt(IDC_EDIT6, 1000);
	pMainFrm->m_pMainView->m_iMoney =  GetDlgItemInt(IDC_EDIT6);
}

/* 콤보 박스 */
void CMonster::OnCbnSelchangeCombo1()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CString		str = L"";
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Combo.GetLBText(m_Combo.GetCurSel(), str);

	pMainFrm->m_pMainView->m_iSelectTileID = -1;
	pMainFrm->m_pMainView->m_iSelectObjID = -1;
	pMainFrm->m_pMainView->m_iSelectWarpID = -1;
	pMainFrm->m_pMainView->m_iSelectNPCID = -1;
	if(str == L"고블린")
	{
		m_Picture.SetBitmap(m_Bitmap[0]);
		pMainFrm->m_pMainView->m_iSelectMonsterID = 1;
	}
	else if(str == L"슬라임")
	{
		m_Picture.SetBitmap(m_Bitmap[1]);
		pMainFrm->m_pMainView->m_iSelectMonsterID = 2;
	}
	else
	{
		m_Picture.SetBitmap(m_Bitmap[2]);
		pMainFrm->m_pMainView->m_iSelectMonsterID = 3;
	}

	str.ReleaseBuffer();
}

void CMonster::OnDestroy()
{
	CPropertyPage::OnDestroy();

	m_Atk.ReleaseBuffer();
	m_HP.ReleaseBuffer();
	m_MP.ReleaseBuffer();
	m_Def.ReleaseBuffer();
	m_Exp.ReleaseBuffer();
	m_Money.ReleaseBuffer();

	for(int i = 0 ; i < MONSTER_CNT ; ++i)
	{
		DeleteObject(m_Bitmap[i]);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CMonster::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	TCHAR szTmp[128] = L"";
	RECT rcPicture = { 0, 0, 100, 100};

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Combo.AddString(L"고블린");
	m_Combo.AddString(L"슬라임");
	m_Combo.AddString(L"타락천사");

	m_Picture.GetWindowRect(&rcPicture);
	SetRect(&rcPicture, 0, 0, rcPicture.right - rcPicture.left, rcPicture.bottom - rcPicture.top);
	
	m_Bitmap[0] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/Monster/Goblin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Bitmap[1] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/Monster/Slime.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Bitmap[2] = (HBITMAP)LoadImage(NULL, L"../Resource/Texture/Monster/Boss/Boss_Face.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMonster::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iAttack = GetDlgItemInt(IDC_EDIT1);
}

void CMonster::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iHP = GetDlgItemInt(IDC_EDIT3);
}


void CMonster::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iMP = GetDlgItemInt(IDC_EDIT4);
}

void CMonster::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iDefence = GetDlgItemInt(IDC_EDIT7);
}

void CMonster::OnEnChangeEdit5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iExp = GetDlgItemInt(IDC_EDIT5);
}

void CMonster::OnEnChangeEdit6()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMainFrm->m_pMainView->m_iMoney = GetDlgItemInt(IDC_EDIT6);
}
