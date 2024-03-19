#include "stdafx.h"
#include "Flower.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CFlower::CFlower()
{
}

CFlower::~CFlower()
{
	Release();
}

void CFlower::Initialize(void)
{
	m_tInfo = { 200.f, 100.f, 32.f, 32.f };

	MBITMAP->Insert_Bmp(L"../Image/Item/Flower.bmp", L"Flower");

	m_pFrameKey = L"Flower";
	m_eCurState = IDLE;
	m_ePreState = STATE_END;
	m_fSpeed = 5.0f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();
}

int CFlower::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CFlower::Late_Update(void)
{
	Motion_Change();

	__super::Move_Frame();
}

void CFlower::Render(HDC hDC)
{
	int		iScrollX = (int)MSCROLL->Get_ScrollX();

	HDC		hMemDC = MBITMAP->Find_Img(L"Flower");

	GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
		int(m_tRect.left + iScrollX), // 복사 받을 텍스처 위치 좌표 X
		int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
		int(m_tInfo.fCX), // 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 텍스처 세로 사이즈
		hMemDC,	// 복사할 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 6),	// 비트맵 출력 좌표 X
		0,	// 비트맵 출력 좌표 Y
		int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상
}

void CFlower::Release(void)
{
}

void CFlower::Key_Input()
{
	if (GetAsyncKeyState('F'))
	{
		m_bDead = true;
	}
}

void CFlower::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case SPARKLING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CFlower::Flower_Dead()
{
}
