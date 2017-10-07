
// MaptoolView.h : CMaptoolView 클래스의 인터페이스
//

#pragma once

#include "Define.h"
#include "MaptoolDoc.h"
#include "MiniMap.h"

class CMaptoolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMaptoolView();
	DECLARE_DYNCREATE(CMaptoolView)

// 특성입니다.
public:
	CMaptoolDoc* GetDocument() const;

// 작업입니다.
public:
	vector<TILE*>		m_vecTile;
	vector<OBJECT*>		m_vecObj;
	vector<SYSTEM*>		m_vecSys;
	vector<MONSTER*>	m_vecMon;
	vector<NPC*>		m_vecNPC;

	/* Sheet에서 선택된 몬스터 스탯 저장용 */
	int					m_iLevel;
	int					m_iAttack;
	int					m_iHP;
	int					m_iMP;
	int					m_iDefence;
	int					m_iExp;
	int					m_iMoney;
	enum MONSTER_CLASS	m_MonsterClass;

	/* Sheet에서 선택된 NPC 스탯 저장용 */
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
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMaptoolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // MaptoolView.cpp의 디버그 버전
inline CMaptoolDoc* CMaptoolView::GetDocument() const
   { return reinterpret_cast<CMaptoolDoc*>(m_pDocument); }
#endif

