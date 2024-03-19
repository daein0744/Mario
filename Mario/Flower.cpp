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

	GdiTransparentBlt(hDC,		// ���� ���� ���� DC
		int(m_tRect.left + iScrollX), // ���� ���� �ؽ�ó ��ġ ��ǥ X
		int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		int(m_tInfo.fCX), // �ؽ�ó ���� ������
		int(m_tInfo.fCY), // �ؽ�ó ���� ������
		hMemDC,	// ������ DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 6),	// ��Ʈ�� ��� ��ǥ X
		0,	// ��Ʈ�� ��� ��ǥ Y
		int(m_tInfo.fCX), // ������ ��Ʈ�� �ؽ�ó ���� ������
		int(m_tInfo.fCY), // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����
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
