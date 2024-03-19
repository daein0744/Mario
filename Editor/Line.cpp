#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}


CLine::CLine(MYPOINT& tLeft, MYPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{
}

CLine::CLine(LINE& tLine)
{
	memcpy(&m_tInfo, &tLine, sizeof(LINE));
}

CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(_hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(_hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY);
}
