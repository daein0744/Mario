#include "stdafx.h"
#include "Obj.h"
#include "Block.h"

CObj::CObj()
	:m_bDead(false), m_fSpeed(0), m_eObjID(OBJ_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::Hit(CObj * _pTarget)
{
}

void CObj::Hit_Up(CObj * _pTarget)
{
}

void CObj::Hit_Down(CObj * _pTarget)
{
}

void CObj::Hit_LeftRight(CObj * _pTarget)
{
}

void CObj::Update_Rect()
{
	m_tRect = { long(m_tInfo.fX - m_tInfo.fCX * 0.5f),
		long(m_tInfo.fY - m_tInfo.fCY * 0.5f),
		long(m_tInfo.fX + m_tInfo.fCX * 0.5f),
		long(m_tInfo.fY + m_tInfo.fCY * 0.5f),
	};
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}
