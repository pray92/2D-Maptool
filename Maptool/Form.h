#pragma once

#include "MySheet.h"

// CForm �� ���Դϴ�.

class CForm : public CFormView
{
	DECLARE_DYNCREATE(CForm)
private:
	CString		m_strTile;
	CString		m_strObj;
	CString		m_strWarp;
	CString		m_strNPC;
	CString		m_strMon;

	CMySheet*	m_pMySheet;
protected:
	CForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CForm();

public:
	enum { IDD = IDD_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDestroy();
};


