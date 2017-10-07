
// MaptoolView.h : CMaptoolView Ŭ������ �������̽�
//

#pragma once

#include "Define.h"
#include "MaptoolDoc.h"
#include "MiniMap.h"

class CMaptoolView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMaptoolView();
	DECLARE_DYNCREATE(CMaptoolView)

// Ư���Դϴ�.
public:
	CMaptoolDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	vector<TILE*>		m_vecTile;
	vector<OBJECT*>		m_vecObj;
	vector<SYSTEM*>		m_vecSys;
	vector<MONSTER*>	m_vecMon;
	vector<NPC*>		m_vecNPC;

	/* Sheet���� ���õ� ���� ���� ����� */
	int					m_iLevel;
	int					m_iAttack;
	int					m_iHP;
	int					m_iMP;
	int					m_iDefence;
	int					m_iExp;
	int					m_iMoney;
	enum MONSTER_CLASS	m_MonsterClass;

	/* Sheet���� ���õ� NPC ���� ����� */
	enum NPC_CLASS		m_NPCClass;

	int					m_iSelectTileID;
	int					m_iSelectObjID;
	int					m_iSelectWarpID;
	int					m_iSelectMonsterID;
	int					m_iSelectNPCID;
	
	CMiniMap*	m_pMiniMap;
public:
	void InitTile();
	void InitObj();
	void InitSystem();
	void InitMonster();
	void InitNPC();

	bool CollisionMouseToTile(D3DXVECTOR3 vMousePoint,const TILE* pTileInfo);

	RECT GetTileDraw(int _iIndex);
	RECT GetRootDraw(int _iIndex);
	RECT GetObjDraw(int _iDrawID);
	RECT GetWarpDraw(int _iDrawID);
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMaptoolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MaptoolView.cpp�� ����� ����
inline CMaptoolDoc* CMaptoolView::GetDocument() const
   { return reinterpret_cast<CMaptoolDoc*>(m_pDocument); }
#endif

