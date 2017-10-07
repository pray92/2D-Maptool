#pragma once
class CObj
{
protected:
	OBJ_INFO			m_Info;
protected:
	TCHAR*				m_pObjKey;
	TCHAR*				m_pStateKey;
protected:
	static D3DXVECTOR3	m_vScroll;
	static D3DXVECTOR3	m_vOffset;
protected:
	SORT_ID				m_SortID;
	float				m_fFrame;
	FRAME				m_tFrame;
protected:
	OBJ_INFO	SetMouseInfo();
	D3DXVECTOR3* GetScroll() const { return &m_vScroll; }
	int			GetTileIndex(const D3DXVECTOR3& vPos);
	bool		CollsionMouseToTile(D3DXVECTOR3 vMousePoint,const TILE* pTileInfo);
public:
	OBJ_INFO GetObjInfo(){ return m_Info; }
	SORT_ID GetSortID(){ return m_SortID; }
public:
	void Multi_Frame_Move(const float& _fCnt, const float& _fMax);

	void Single_Frame_Move(const float& _fCnt);
	void SetScene(const float& _fLast, const int& _iScene);
public:
	virtual HRESULT	Initialize() PURE;
	virtual SCENE Progress() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual CObj* Clone() PURE;
public:
	CObj(void);
	CObj(const OBJ_INFO& _Info);
	virtual ~CObj(void);
};

