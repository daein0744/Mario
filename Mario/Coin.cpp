#include "stdafx.h"
#include "Coin.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CCoin::CCoin()
{
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize(void)
{
	m_tInfo = { 100.f, 200.f, 16.f, 28.f };

	MBITMAP->Insert_Bmp(L"../Image/Item/Coin.bmp", L"Coin");
	MBITMAP->Insert_Bmp(L"../Image/Item/SparklingCoin.bmp", L"SparklingCoin");

	m_pFrameKey = L"Coin";
	m_eCurState = IDLE;
	m_ePreState = STATE_END;
	m_pFrameKey = L"";
	m_fSpeed = 5.0f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();

	m_bStart = true;
	m_bMove = true;
	fY = 0.f;
	fDeadLine = 0.f;
}

int CCoin::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pFrameKey = L"SparklingCoin";
	Moving_UD();
	m_eCurState = IDLE;
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Late_Update(void)
{
	Motion_Change();

	__super::Move_Frame();
}

void CCoin::Render(HDC hDC)
{
	int		iScrollX = (int)MSCROLL->Get_ScrollX();

	HDC		hMemDC = MBITMAP->Find_Img(m_pFrameKey);

	if (L"SparklingCoin" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
			int(m_tRect.left + iScrollX), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,	// 복사할 DC
			m_tFrame.iFrameStart * (int(m_tInfo.fCX + 2)),	// 비트맵 출력 좌표 X
			0,	// 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}

	else
	{
		GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
			int(m_tRect.left + iScrollX), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,	// 복사할 DC
			m_tFrame.iFrameStart * int(m_tInfo.fCX + 8),	// 비트맵 출력 좌표 X
			0,	// 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}
}

void CCoin::Release(void)
{
}


void CCoin::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case SPARKLING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CCoin::Moving_UD()
{
	m_eCurState = SPARKLING;

	if (m_bStart)
	{
		fY = m_tInfo.fY - 100.f;
		fDeadLine = m_tInfo.fY - m_tInfo.fCY * 0.5f;
		m_bStart = false;
	}

	else
	{
		if (m_bMove)
		{
			m_tInfo.fY -= m_fSpeed;
			if (fY == m_tInfo.fY)
				m_bMove = false;
		}

		else
		{
			m_tInfo.fY += m_fSpeed;
			if (fDeadLine <= m_tInfo.fY)
				m_bDead = true;
		}
	}
}