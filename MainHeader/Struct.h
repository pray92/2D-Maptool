#pragma once

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO	   ImgInfo;
}TEXINFO;

typedef struct tagFrame
{
	float		fStart;
	float		fLast;
	int			iScene;
	DWORD	dwTime;

	tagFrame(){}
	tagFrame(float		_fStart,
			 float		_fLast,
			 int		_iScene,
			 DWORD	_dwTime)
	{
		fStart  = _fStart;
		fLast	= _fLast;
		iScene	= _iScene;
		dwTime	= _dwTime;
	}
}FRAME;

typedef struct tagObjInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vCenter;			
	D3DXMATRIX		matWorld;

	tagObjInfo(){};
	tagObjInfo(const tagObjInfo& _Info)
		:vPos(_Info.vPos), vSize(_Info.vSize), vDir(_Info.vDir), vLook(_Info.vLook), vCenter(_Info.vCenter), matWorld(_Info.matWorld)
	{
	}
}OBJ_INFO;

typedef struct tagInfo
{
	TCHAR szName[128];
	int iLevel;
	int iAttack;
	int iCurHP;
	int iHP;
	int iCurMP;
	int iMP;
	int iDefence;
	int iCurExp;
	int iExp;
	int iMoney;

	tagInfo()
	{
		ZeroMemory(this,sizeof(INFO));
	}
	tagInfo(TCHAR* _szName, int _iLevel, int _iAttack, 
			int _iHP, int _iMP, 
			int _iDefence, int _iExp, 
			int _iMoney)
			:iLevel(_iLevel), iAttack(_iAttack),
			iHP(_iHP), iMP(_iMP),
			iDefence(_iDefence), iExp(_iExp),
			iMoney(_iMoney)
	{
		ZeroMemory(szName, sizeof(szName));
		lstrcpy(szName, _szName);
		iCurHP = _iHP;
		iCurMP = _iMP;
		iCurExp = _iExp;
	}
}INFO;

typedef struct tagPlayer
{
	OBJ_INFO		tObjInfo;
	DWORD			dwState;
	INFO			tInfo;
}PLAYER;

typedef struct tagTile
{
	D3DXVECTOR3		vTilePos;
	D3DXVECTOR3		vTileSize;

	D3DXVECTOR3		vRootPos;
	D3DXVECTOR3		vRootSize;

	BYTE			byDrawId;
	BYTE			byOption;
}TILE;

typedef struct tagObj
{
	D3DXVECTOR3		vObjPos;
	BYTE			byDrawId;
}OBJECT;

typedef struct tagNPC
{
	OBJ_INFO		tObjInfo;
	int				iStartDir;
	NPC_CLASS		eClass;
	BYTE			byDrawId;
}NPC;

typedef struct tagMonster
{
	OBJ_INFO		tObjInfo;
	MONSTER_CLASS	eClass;
	DWORD			dwState;
	INFO			tInfo;
	BYTE			byDrawId;
}MONSTER;

typedef struct tagSystem
{
	D3DXVECTOR3		vSysPos;
	BYTE			byDrawId;
}SYSTEM;

typedef struct AStarNode
{
	float		fCost;
	int			iIndex;
	AStarNode*	pParent;
}NODE;