#pragma once
#include "afxwin.h"

#define NPC_CNT 3
// CNPC 대화 상자입니다.

class CNPC : public CPropertyPage
{
	DECLARE_DYNAMIC(CNPC)	
public:
	HBITMAP		m_Bitmap[NPC_CNT];
public:
	CNPC();
	virtual ~CNPC();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_Combo;
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	CStatic m_Picture;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
};
