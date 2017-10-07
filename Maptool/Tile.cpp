// Tile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Maptool.h"
#include "Tile.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MaptoolView.h"

// CTile 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTile, CPropertyPage)

CTile::CTile()
	: CPropertyPage(CTile::IDD)
{

}

CTile::~CTile()
{
}

void CTile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_TREE1, m_RootTree);
}


BEGIN_MESSAGE_MAP(CTile, CPropertyPage)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTile::OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTile::OnLbnSelchangeList1)
	ON_STN_CLICKED(IDC_PICTURE, &CTile::OnStnClickedPicture)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CTile::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDOK, &CTile::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTile::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTile 메시지 처리기입니다.


void CTile::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (int i =0; i < ARRAY_SIZE; ++i)
	{
		DeleteObject(m_BitMap[i]);
	}
}

BOOL CTile::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	TCHAR szTmp[128] = L"";
	RECT rcPicture;

	m_Picture.GetWindowRect(&rcPicture);
	SetRect(&rcPicture, 0, 0, rcPicture.right - rcPicture.left, rcPicture.bottom - rcPicture.top);
	
	HTREEITEM Map = m_RootTree.InsertItem(L"맵", TVI_ROOT, TVI_LAST);

	HTREEITEM Tile = m_RootTree.InsertItem(L"타일", Map, TVI_LAST);
	HTREEITEM TileAry[TILE_CNT];
	
	HTREEITEM Object = m_RootTree.InsertItem(L"오브젝트", Map, TVI_LAST);
	HTREEITEM ObjAry[OBJ_CNT];

	HTREEITEM Warp = m_RootTree.InsertItem(L"워프", Map, TVI_LAST);
	HTREEITEM WarpAry[WARP_CNT];

	for(int i = 0 ; i < TILE_CNT ; ++i)
	{
		wsprintf(szTmp, L"Tile%d", i);
		TileAry[i] = m_RootTree.InsertItem(szTmp, Tile, TVI_LAST);
		wsprintf(szTmp,L"../Resource/Texture/Map/Map%d.bmp",i);
		m_BitMap[i] = (HBITMAP)LoadImage(NULL,szTmp,IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
	}

	for(int i = 1 ; i < OBJ_CNT ; ++i)
	{
		wsprintf(szTmp, L"Object%d", i);
		ObjAry[i] = m_RootTree.InsertItem(szTmp, Object, TVI_LAST);

		wsprintf(szTmp,L"../Resource/Texture/Map/Object%d.bmp",i);
		m_BitMap[TILE_CNT + i - 1] = (HBITMAP)LoadImage(NULL,szTmp,IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
	}

	for(int i = 1 ; i < WARP_CNT ; ++i)
	{
		wsprintf(szTmp, L"Warp%d", i);
		WarpAry[i] = m_RootTree.InsertItem(szTmp, Warp, TVI_LAST);

		wsprintf(szTmp,L"../Resource/Texture/System/Warp%d.bmp",i);
		m_BitMap[TILE_CNT + OBJ_CNT + i - 1] = (HBITMAP)LoadImage(NULL,szTmp,IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
	}
	//m_Picture.SetBitmap(m_BitMap[0]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTile::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CTile::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//int iIndex = m_List.GetCurSel();

	//m_Picture.SetBitmap(m_BitMap[iIndex]);

	//CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	//pMainFrm->m_pMainView->m_iSelectDrawID = iIndex;
}

void CTile::OnStnClickedPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CTile::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szTmp[128] = L"";
	m_hSelectItem = pNMTreeView->itemNew.hItem;
	
	CString strTmp = m_RootTree.GetItemText(m_hSelectItem);

	for(int i = 0 ; i < ARRAY_SIZE ; ++i)
	{
		if(i < TILE_CNT)
		{
			wsprintf(szTmp, L"Tile%d", i);
			if(strTmp == szTmp)
			{
				m_Picture.SetBitmap(m_BitMap[i]);
				CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
				pMainFrm->m_pMainView->m_iSelectObjID = -1;
				pMainFrm->m_pMainView->m_iSelectWarpID = -1;
				pMainFrm->m_pMainView->m_iSelectMonsterID = -1;
				pMainFrm->m_pMainView->m_iSelectNPCID = -1;
				pMainFrm->m_pMainView->m_iSelectTileID = i;
				break;
			}
		}
		else if(TILE_CNT <= i && i < TILE_CNT + OBJ_CNT)
		{
			wsprintf(szTmp, L"Object%d", i - TILE_CNT + 1);
			if(strTmp == szTmp)
			{
				m_Picture.SetBitmap(m_BitMap[i]);
				CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
				pMainFrm->m_pMainView->m_iSelectTileID = -1;
				pMainFrm->m_pMainView->m_iSelectWarpID = -1;
				pMainFrm->m_pMainView->m_iSelectMonsterID = -1;
				pMainFrm->m_pMainView->m_iSelectNPCID = -1;
				pMainFrm->m_pMainView->m_iSelectObjID = i - TILE_CNT + 1;
				break;
			}
		}
		else
		{
			wsprintf(szTmp, L"Warp%d", i - TILE_CNT - OBJ_CNT + 1);
			if(strTmp == szTmp)
			{
				m_Picture.SetBitmap(m_BitMap[i]);
				CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
				pMainFrm->m_pMainView->m_iSelectTileID = -1;
				pMainFrm->m_pMainView->m_iSelectObjID = -1;
				pMainFrm->m_pMainView->m_iSelectMonsterID = -1;
				pMainFrm->m_pMainView->m_iSelectNPCID = -1;
				pMainFrm->m_pMainView->m_iSelectWarpID = i - TILE_CNT - OBJ_CNT + 1;
				break;
			}
		}
	}

	strTmp.ReleaseBuffer();

	*pResult = 0;
}

/* 미사용 */
void CTile::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dig(FALSE,L"dat",L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",this);

	if(Dig.DoModal() == IDCANCEL)
		return;

	HANDLE	hFile;
	DWORD	dwByte;

	hFile = CreateFile(Dig.GetPathName(), GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);


	CMainFrame*  pMainFrm = (CMainFrame*)AfxGetMainWnd();

	/* 타일 저장 */
	for(vector<TILE*>::iterator iter = pMainFrm->m_pMainView->m_vecTile.begin();
		iter != pMainFrm->m_pMainView->m_vecTile.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(TILE),&dwByte,NULL);
	}
	
	/* 오브젝트 저장 */
	for(vector<OBJECT*>::iterator iter = pMainFrm->m_pMainView->m_vecObj.begin();
		iter != pMainFrm->m_pMainView->m_vecObj.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(OBJECT),&dwByte,NULL);
	}

	/* 워프 저장 */
	for(vector<SYSTEM*>::iterator iter = pMainFrm->m_pMainView->m_vecSys.begin();
		iter != pMainFrm->m_pMainView->m_vecSys.end(); ++iter )
	{
		WriteFile(hFile,*iter,sizeof(SYSTEM),&dwByte,NULL);
	}

	CloseHandle(hFile);

}

void CTile::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dig(FALSE,L"dat",L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",this);

	if(Dig.DoModal() == IDCANCEL)
		return;

	CMainFrame*  pMainFrm = (CMainFrame*)AfxGetMainWnd();

	int iVecTileSize = pMainFrm->m_pMainView->m_vecTile.size();
	for(vector<TILE*>::iterator iter = pMainFrm->m_pMainView->m_vecTile.begin();
		iter != pMainFrm->m_pMainView->m_vecTile.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecTile.clear();
	
	int iVecObjSize = pMainFrm->m_pMainView->m_vecObj.size();;
	for(vector<OBJECT*>::iterator iter = pMainFrm->m_pMainView->m_vecObj.begin();
		iter != pMainFrm->m_pMainView->m_vecObj.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}
	pMainFrm->m_pMainView->m_vecObj.clear();

	int iVecWarpSize = pMainFrm->m_pMainView->m_vecSys.size();;
	for(vector<SYSTEM*>::iterator iter = pMainFrm->m_pMainView->m_vecSys.begin();
		iter != pMainFrm->m_pMainView->m_vecSys.end(); ++iter )
	{
		delete *iter;
		*iter = NULL;
	}

	pMainFrm->m_pMainView->m_vecSys.clear();

	HANDLE	hFile;
	DWORD	dwByte;

	hFile = CreateFile(Dig.GetPathName(), GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	
	for(size_t i = 0 ; i < iVecTileSize ; ++i)
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

	for(size_t i = 0 ; i < iVecObjSize ; ++i)
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

	for(size_t i = 0 ; i < iVecWarpSize ; ++i)
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

	//while(true)
	//{
	//	TILE*	pInfo = new TILE;
	//	ReadFile(hFile,pInfo,sizeof(TILE),&dwByte,NULL);
	//	if(dwByte == 0)
	//	{
	//		delete pInfo;
	//		pInfo = NULL;
	//		break;
	//	}
	//	pMainFrm->m_pMainView->m_vecTile.push_back(pInfo);
	//}

	CloseHandle(hFile);
}
