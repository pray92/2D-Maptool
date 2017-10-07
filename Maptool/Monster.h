#pragma once
#include "afxwin.h"

#define MONSTER_CNT 3
// CMonster 대화 상자입니다.

class CMonster : public CPropertyPage
{
	DECLARE_DYNAMIC(CMonster)
public:
	HBITMAP		m_Bitmap[MONSTER_CNT];
public:
	CMonster();
	virtual ~CMonster();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MONSTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_Combo;
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	CStatic m_Picture;
	CString m_Atk;
	CString m_HP;
	CString m_MP;
	CString m_Def;
	CString m_Exp;
	CString m_Money;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
};
