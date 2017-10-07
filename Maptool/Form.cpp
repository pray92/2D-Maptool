// Form.cpp : 구현 파일입니다.
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


// CForm 진단입니다.

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


// CForm 메시지 처리기입니다.


void CForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_pMySheet = new CMySheet();
	m_pMySheet->Create(this, WS_VISIBLE | WS_CHILD);
	m_pMySheet->MoveWindow(0,0, 265, 400, FALSE);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CForm::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

/* 저장 */
void CForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dig(FALSE, NULL,L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",this);

	if(Dig.DoModal() == IDCANCEL)
		return;

	HANDLE	hFile;
	DWORD	dwByte;

	CMainFrame*  pMainFrm = (CMainFrame*)AfxGetMainWnd();

	/* 타일 저장 */	
	hFile = CreateFile(Dig.GetPathName() + L".dat", GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<TILE*>::iterator iter = pMainFrm->m_pMainView->m_vecTile.begin();
		iter != pMainFrm->m_pMainView->m_vecTile.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(TILE),&dwByte,NULL);
	}

	CloseHandle(hFile);
	
	/* 오브젝트 저장 */
	hFile = CreateFile(Dig.GetPathName() + L"_OBJ.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<OBJECT*>::iterator iter = pMainFrm->m_pMainView->m_vecObj.begin();
		iter != pMainFrm->m_pMainView->m_vecObj.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(OBJECT),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* NPC 저장 */

	hFile = CreateFile(Dig.GetPathName() + L"_NPC.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<NPC*>::iterator iter = pMainFrm->m_pMainView->m_vecNPC.begin();
		iter != pMainFrm->m_pMainView->m_vecNPC.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(NPC),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* 몬스터 저장 */
	hFile = CreateFile(Dig.GetPathName() + L"_MON.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<MONSTER*>::iterator iter = pMainFrm->m_pMainView->m_vecMon.begin();
		iter != pMainFrm->m_pMainView->m_vecMon.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(MONSTER),&dwByte,NULL);
	}

	CloseHandle(hFile);

	/* 워프 저장 */

	hFile = CreateFile(Dig.GetPathName() + L"_WARP.dat", GENERIC_WRITE,0,NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

	for(vector<SYSTEM*>::iterator iter = pMainFrm->m_pMainView->m_vecSys.begin();
		iter != pMainFrm->m_pMainView->m_vecSys.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(SYSTEM),&dwByte,NULL);
	}

	CloseHandle(hFile);
}

/* 불러오기 */
void CForm::OnBnClickedButton2()
{	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	
	/* 타일 불러오기 */
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
	
	/* 오브젝트 불러오기 */
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

	/* NPC 불러오기 */
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

	/* 몬스터 불러오기 */
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

	/* 워프 불러오기 */
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_strTile.ReleaseBuffer();
	m_strObj.ReleaseBuffer();
	m_strWarp.ReleaseBuffer();
	m_strNPC.ReleaseBuffer();
	m_strMon.ReleaseBuffer();

	delete m_pMySheet;
}
