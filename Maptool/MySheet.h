#pragma once

#include "Tile.h"
#include "Monster.h"
#include "NPC.h"

// CMySheet

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)
public:
	CTile		m_TilePage;
	CMonster	m_MonsterPage;
	CNPC		m_NPCPage;
	
public:
	CMySheet();
	CMySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMySheet();

protected:
	DECLARE_MESSAGE_MAP()
};


