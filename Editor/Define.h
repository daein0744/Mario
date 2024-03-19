#pragma once
#define		PURE		= 0
#define		WINCX		800
#define		WINCY		600
#define		OBJ_NOEVENT 0
#define		OBJ_DEAD	1

#define			PI		3.141592f

extern			HWND	g_hWnd;

#define		VK_MAX		0xff


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


enum DIRECTION { LEFT, RIGHT, DIR_END };
enum OBJID { PLAYER, OBJ_END };