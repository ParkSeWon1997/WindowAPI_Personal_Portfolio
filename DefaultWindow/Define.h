#pragma once

#define			WINCX		1280
#define			WINCY		800

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI		3.141592f
#define			VK_MAX		 0xff

#define			TILEX		30
#define			TILEY		20

#define			TILECX		32
#define			TILECY		32
		
#define			MyTILECX	16
#define			MyTILECY	16

#define			MYTILEX		16
#define			MYTILEY		16

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;

}INFO;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU,DIR_LD,DIR_RD, DIR_END };
enum OBJID	   { PLAYER, 
				BULLET,
				SUB_MONSTER_BULLET,
				SUB_MONSTER_G_BULLET,
				MONSTER,
				BOSS_MONSTER,
				BOSS_BULLET,
				MOUSE,
				ENTRY,
				STAGE_ENTRY,
				SHIELD,
				BUTTON,
				PlAYER_UI,
				PLAYER_WEAPON_BOX,
				MOSTER_UI,
				GUN,
				SWORD,
				WALL,
				GROUND,
				SNOW,
				COLLISIONBOX,
				ITEM_HP,
				ITEM_BOX,
				ID_NPC,
				OBJ_END };
enum SCENEID	{ SC_LOGO, SC_MENU, SC_EDIT, SC_VILLAGE,SC_NORMAL,SC_BOSS, SC_END };



enum WEAPONMODE { PLAYER_GUN, PLAYER_SWORD, PLAYE_RDRAGON_SWORD, WEAPON_END };

enum RENDERID	{ BACKGROUND, GAMEOBJECT, EFFECT, UI, RENDER_END};

enum CHANNELID { SOUND_EFFECT,
	SOUND_PLAYER_WALK,
	PLAYER_SWING,
	PLAYER_FIRE,
	MONSTER_DEAD,
	MONSTER_ATTACK,
	STAGE_WORK,
	SOUND_HIT,
	SOUND_PLAYER_DEAD,
	SOUND_BGM_BG,
	SOUND_BGM,
	MAXCHANNEL };


enum SUBMOSTER_STATE { IDLE, ATTACK, TARGET_SHOT, MOVE_TO_BOSS, SUB_STATE_END };

enum BOSSMONSTER_SPEAR_DIR {MOVE_RIGHT,MOVE_LEFT,MOVE_UP,MOVE_DOWN ,BOSS_SPEAR_END};
enum BOSS_STATE { SC_BOSS_CREATE_SUB, SC_BOSS_IDLE, SC_BOSS_EASY, SC_BOSS_NORMAL, SC_BOSS_HARD, SC__BOSS_DEAD, SC_BOSS_END };

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct CDeleteObj
{
	template<typename T>
	void	operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

struct CDeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

struct CTagFinder
{
	CTagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool		operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}


	const TCHAR*		m_pString;
};



typedef struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {  }

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& tLeft, LINEPOINT& tRight)
		: tLPoint(tLeft), tRPoint(tRight) {}

}LINE;

typedef struct tagFrame
{
	int mCurIndexFrame;
	float mAnitime;
	float mTimeInterval;
	int mTotalFrameCount;
	bool	bStopMotionChanger;



	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;



	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;



extern		HWND		g_hWnd;
