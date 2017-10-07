#pragma once
#include "villagestatic.h"
class CVillageMap :
	public CVillageStatic
{
private:
	vector<TILE*>			m_vecTile;
	D3DXMATRIX				matWorld;

	/* 마우스 타일용 */
	vector<TILE*>			m_vecTmp;
	RECT					rcMouse;
public:
	void InitTileFromFile();
	RECT GetTileDraw(int _iIndex);
	RECT GetRootDraw(int _iIndex);
public:
	void MapScroll();
	const vector<TILE*>* GetTileInfo(){ return &m_vecTile; }
	const vector<TILE*>* GetTmpInfo(){ return &m_vecTmp; }
public:
	virtual HRESULT	Initialize(void);
	virtual SCENE Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CVillageMap(void);
	CVillageMap(const OBJ_INFO& _Info);
	~CVillageMap(void);
};

