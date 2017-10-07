// Form.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Maptool.h"
#include "Form.h"

#include "MainFrm.h"
#include "MaptoolView.h"

// CForm

IMPLEMENT_DYNCREATE(CForm, CFormView)

CForm::CForm()
	: CFormView(CForm::IDD)
{

}

CForm::~CForm()
{
}

void CForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm, CFormView)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CForm::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CForm::OnBnClickedButton2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CForm �����Դϴ�.

#ifdef _DEBUG
void CForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm �޽��� ó�����Դϴ�.


void CForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_pMySheet = new CMySheet();
	m_pMySheet->Create(this, WS_VISIBLE | WS_CHILD);
	m_pMySheet->MoveWindow(0,0, 265, 400, FALSE);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CForm::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

/* ���� */
void CForm::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dig(FALSE, NULL,L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",this);

	if(Dig.DoModal() == IDCANCEL)
		return;

	HANDLE	hFile;
	DWORD	dwByte;

	CMainFrame*  pMainFrm = (CMainFrame*)AfxGetMainWnd();

	/* Ÿ�� ���� */	
	hFile = CreateFile(Dig.GetPathName() + L".dat", GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<TILE*>::iterator iter = pMainFrm->m_pMainView->m_vecTile.begin();
		iter != pMainFrm->m_pMainView->m_vecTile.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(TILE),&dwByte,NULL);
	}

	CloseHandle(hFile);
	
	/* ������Ʈ ���� */
	hFile = CreateFile(Dig.GetPathName() + L"_OBJ.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<OBJECT*>::iterator iter = pMainFrm->m_pMainView->m_vecObj.begin();
		iter != pMainFrm->m_pMainView->m_vecObj.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(OBJECT),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* NPC ���� */

	hFile = CreateFile(Dig.GetPathName() + L"_NPC.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<NPC*>::iterator iter = pMainFrm->m_pMainView->m_vecNPC.begin();
		iter != pMainFrm->m_pMainView->m_vecNPC.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(NPC),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* ���� ���� */
	hFile = CreateFile(Dig.GetPathName() + L"_MON.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<MONSTER*>::iterator iter = pMainFrm->m_pMainView->m_vecMon.begin();
		iter != pMainFrm->m_pMainView->m_vecMon.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(MONSTER),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* ���� ���� */

	hFile = CreateFile(Dig.GetPathName() + L"_WARP.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<SYSTEM*>::iterator iter = pMainFrm->m_pMainView->m_vecSys.begin();
		iter != pMainFrm->m_pMainView->m_vecSys.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(SYSTEM),&dwByte,NULL);
	}

	CloseHandle(hFile);
}

/* �ҷ����� */
void CForm::OnBnClickedButton2()
{	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dig( true, NULL,L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",this);

	if(Dig.DoModal() == IDCANCEL)
		return;

	CMainFrame*  pMainFrm = (CMainFrame*)AfxGetMainWnd();

	for(vector<TILE*>::iterator iter = pMainFrm->m_pMainView->m_vecTile.begin();
		iter != pMainFrm->m_pMainView->m_vecTile.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecTile.clear();
	
	for(vector<OBJECT*>::iterator iter = pMainFrm->m_pMainView->m_vecObj.begin();
		iter != pMainFrm->m_pMainView->m_vecObj.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecObj.clear();

	for(vector<NPC*>::iterator iter = pMainFrm->m_pMainView->m_vecNPC.begin();
		iter != pMainFrm->m_pMainView->m_vecNPC.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecNPC.clear();

	for(vector<MONSTER*>::iterator iter = pMainFrm->m_pMainView->m_vecMon.begin();
		iter != pMainFrm->m_pMainView->m_vecMon.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecMon.clear();

	for(vector<SYSTEM*>::iterator iter = pMainFrm->m_pMainView->m_vecSys.begin();
		iter != pMainFrm->m_pMainView->m_vecSys.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecSys.clear();

	HANDLE	hFile;
	DWORD	dwByte;

	m_strTile = Dig.GetPathName();
	m_strTile.Replace(L".dat", L"");
	m_strObj = Dig.GetPathName();
	m_strObj.Replace(L".dat", L"");
	m_strWarp = Dig.GetPathName();
	m_strWarp.Replace(L".dat", L"");
	m_strNPC = Dig.GetPathName();
	m_strNPC.Replace(L".dat", L"");
	m_strMon = Dig.GetPathName();
	m_strMon.Replace(L".dat", L"");


	hFile = CreateFile( m_strTile + L".dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	/* Ÿ�� �ҷ����� */
	while(true)
	{
		TILE*	pInfo = new TILE;
		ReadFile(hFile,pInfo,sizeof(TILE),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		pMainFrm->m_pMainView->m_vecTile.push_back(pInfo);
	}

	CloseHandle(hFile);
	
	/* ������Ʈ �ҷ����� */
	hFile = CreateFile(m_strObj + L"_OBJ.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		OBJECT*	pInfo = new OBJECT;
		ReadFile(hFile,pInfo,sizeof(OBJECT),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		pMainFrm->m_pMainView->m_vecObj.push_back(pInfo);
	}

	CloseHandle(hFile);

	/* NPC �ҷ����� */
	hFile = CreateFile(m_strNPC + L"_NPC.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		NPC*	pInfo = new NPC;
		ReadFile(hFile,pInfo,sizeof(NPC),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		pMainFrm->m_pMainView->m_vecNPC.push_back(pInfo);
	}

	CloseHandle(hFile);

	/* ���� �ҷ����� */
	hFile = CreateFile(m_strMon + L"_MON.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		NPC*	pInfo = new NPC;
		ReadFile(hFile,pInfo,sizeof(NPC),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		pMainFrm->m_pMainView->m_vecNPC.push_back(pInfo);
	}

	CloseHandle(hFile);

	/* ���� �ҷ����� */
	hFile = CreateFile(m_strWarp + L"_WARP.dat", GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	while(true)
	{
		SYSTEM*	pInfo = new SYSTEM;
		ReadFile(hFile,pInfo,sizeof(SYSTEM),&dwByte,NULL);
		if(dwByte == 0)
		{
			delete pInfo;
			pInfo = NULL;
			break;
		}
		pMainFrm->m_pMainView->m_vecSys.push_back(pInfo);
	}

	CloseHandle(hFile);

}

void CForm::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_strTile.ReleaseBuffer();
	m_strObj.ReleaseBuffer();
	m_strWarp.ReleaseBuffer();
	m_strNPC.ReleaseBuffer();
	m_strMon.ReleaseBuffer();

	delete m_pMySheet;
}
