#pragma once

const int WINSIZEX = 800;
const int WINSIZEY = 600;

const int MINISIZEX = 300;
const int MINISIZEY = 300;

const int FORMSIZEX = 300;
const int FORMSIZEY = 300;

const int TILECNTX = 30;
const int TILECNTY = TILECNTX * 4;

const int TILESIZEX = 62;
const int TILESIZEY = 32;

const int TILERTSIZEX = 64;
const int TILERTSIZEY = 32;

/* 맵 정사각형 화 */
const int iShowTile = 16;

const DWORD KEY_UP		=	0x00000001;
const DWORD KEY_DOWN	=	0x00000002;
const DWORD KEY_LEFT	=	0x00000004;
const DWORD KEY_RIGHT	=	0x00000008;
const DWORD KEY_SPACE	=	0x00000010;
const DWORD KEY_RETURN	=	0x00000020;
const DWORD KEY_LBUTTON	=	0x00000040;
const DWORD KEY_RBUTTON	=	0x00000080;

/* 플레이어 및 몬스터 상태 */
const DWORD STATE_STAND		=	0x00000001;
const DWORD STATE_MOVE		=	0x00000002;
const DWORD STATE_DAMAGED	=	0x00000004;
const DWORD STATE_ATTACK	=	0x00000008;
const DWORD STATE_CASTING	=	0x00000010;
const DWORD STATE_SKILL		=	0x00000020;
const DWORD STATE_DEAD		=	0x00000040;

const WINMODE CUR_WINMODE = WINMODE_WIN;

enum TEXTTYPE
{
	TEXTTYPE_SINGLE,
	TEXTTYPE_MULTI,
};