#include "stdafx.h"
#include "Mushroom.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "CollilsionMgr.h"

CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
	Release();
}

void CMushroom::Initialize(void)
{
	m_tInfo = { 250.f, 250.f, 32.f, 32.f };

	MBITMAP->Insert_Bmp(L"../Image/Item/Mushroom.bmp", L"Mushroom");

	m_pFrameKey = L"Mushroom";
	m_eCurState = IDLE;
	m_ePreState = STATE_END;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();

	m_eItemId = MUSHROOM;
}

int CMushroom::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMushroom::Late_Update(void)
{
	__super::Move_Frame();
}

void CMushroom::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();

	HDC hMemDC = MBITMAP->Find_Img(L"Mushroom");

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 6),
		0,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		RGB(1, 1, 1));
}

void CMushroom::Release(void)
{
}

void CMushroom::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
			break;

		case SPARKLING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}