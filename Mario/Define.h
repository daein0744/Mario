#pragma once
#define		PURE		= 0
#define		WINCX		800
#define		WINCY		600
#define		OBJ_NOEVENT 0
#define		OBJ_DEAD	1

#define			PI		3.141592f

extern			HWND	g_hWnd;

#define		VK_MAX		0xff

#define MINI_MARIO_LRUN		 L"Mini_Mario_LRun"
#define MINI_MARIO_RRUN		 L"Mini_Mario_RRun"
#define MINI_MARIO_LIDLE	 L"Mini_Mario_LIdle"
#define MINI_MARIO_RIDLE	 L"Mini_Mario_RIdle"
#define MINI_MARIO_LJUMP	 L"Mini_Mario_LJump"
#define MINI_MARIO_RJUMP	 L"Mini_Mario_RJump"

#define ADULT_MARIO_LRUN	 L"Adult_Mario_LRun"
#define ADULT_MARIO_RRUN	 L"Adult_Mario_RRun"
#define ADULT_MARIO_LIDLE	 L"Adult_Mario_LIdle"
#define ADULT_MARIO_RIDLE	 L"Adult_Mario_RIdle"
#define ADULT_MARIO_LJUMP	 L"Adult_Mario_LJump"
#define ADULT_MARIO_RJUMP	 L"Adult_Mario_RJump"

#define FLOWER_MARIO_LRUN	 L"Flower_Mario_LRun"
#define FLOWER_MARIO_RRUN	 L"Flower_Mario_RRun"
#define FLOWER_MARIO_LIDLE	 L"Flower_Mario_LIdle"
#define FLOWER_MARIO_RIDLE	 L"Flower_Mario_RIdle"
#define FLOWER_MARIO_LJUMP	 L"Flower_Mario_LJump"
#define FLOWER_MARIO_RJUMP	 L"Flower_Mario_RJump"
#define FLOWER_MARIO_LFIRE	 L"Flower_Mario_LFire"
#define FLOWER_MARIO_RFIRE	 L"Flower_Mario_RFire"

#define MOUNTAIN1				L"scene1"
#define MOUNTAIN2				L"scene2"
#define CLOUD1					L"scene3"
#define CLOUD2					L"scene4"
#define CLOUD3					L"scene5"
#define GRASS1					L"scene6"
#define GRASS2					L"scene7"
#define GRASS3					L"scene8"

#define UICOIN					L"scene9"
#define GOALFLAG				L"scene10"

#define BOSSTILE				L"scene11"	
#define BOSSAXE					L"scene12"


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;

}INFO;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;


typedef		struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint(void) { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}MYPOINT;

typedef	struct tagLine
{
	MYPOINT		tLPoint;
	MYPOINT		tRPoint;

	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(MYPOINT& tLeft, MYPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {}

}LINE;


class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};


class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pKey)
		: m_pKey(pKey) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		if (!lstrcmp(MyPair.first, m_pKey))
			return true;

		return false;
	}

private:
	const TCHAR*		m_pKey;
};

enum ITEMID { COIN, FLOWER, MUSHROOM, ITEM_END };
enum SelectMenu { MENU_START, MENU_EDIT, MENU_EXIT, MENU_END };
enum SCENEID { SC_LOGO, SC_MENU, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_STAGE4, SC_DEATH, SC_END };
enum DIRECTION { LEFT, RIGHT, DIR_END };
enum OBJID { PLAYER, MONSTER, ITEM, BULLET, OBJ_END };