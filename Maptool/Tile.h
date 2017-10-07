#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define TILE_CNT	11
#define	OBJ_CNT		26
#define WARP_CNT	8
#define ARRAY_SIZE	TILE_CNT + OBJ_CNT + WARP_CNT
// CTile 대화 상자입니다.

class CTile : public CPropertyPage
{
	DECLARE_DYNAMIC(CTile)
public:
	//CListBox	m_List;
	HBITMAP		m_BitMap[ARRAY_SIZE];
	HTREEITEM	m_hSelectItem;
public:
	CTile();
	virtual ~CTile();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	CStatic m_Picture;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnStnClickedPicture();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTreeCtrl m_RootTree;
};
