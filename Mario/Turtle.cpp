#include "stdafx.h"
#include "Turtle.h"
#include "BitmapMgr.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

CTurtle::CTurtle()
{
}


CTurtle::~CTurtle()
{
	Release();
}

void CTurtle::Initialize(void)
{
	m_tInfo = {1100.f, 100.f, 32.f, 48.f };
	m_fSpeed = 2.f;

	MBITMAP->Insert_Bmp(L"../Image/Monster/Turtle_LMove.bmp", L"Turtle_LMove");
	MBITMAP->Insert_Bmp(L"../Image/Monster/Turtle_RMove.bmp", L"Turtle_RMove");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CTurtle::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Move();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CTurtle::Late_Update(void)
{
	__super::Move_Frame();
}

void CTurtle::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	if (m_fSpeed > 0)
	{
		HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Turtle_LMove");
		GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
			int(m_tRect.left + iScrollX + Player_Speed), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,	// 복사할 DC
			m_tFrame.iFrameStart * int(m_tInfo.fCX + 28),	// 비트맵 출력 좌표 X
			m_tFrame.iMotion * int(m_tInfo.fCY),	// 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}
	else
	{
		HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Turtle_RMove");
		GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
			int(m_tRect.left + iScrollX + Player_Speed), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,	// 복사할 DC
			m_tFrame.iFrameStart * int(m_tInfo.fCX + 28),	// 비트맵 출력 좌표 X
			m_tFrame.iMotion * int(m_tInfo.fCY),	// 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}
}

void CTurtle::Release(void)
{
}

void CTurtle::Move()
{
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// 충돌하면 -1 곱하기

	m_tInfo.fY += 8;
	if (bBlockCol)
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f + 1;
}

void CTurtle::Hit_Up(CObj * _pTarget)
{
	switch (_pTarget->Get_ObjID())
	{
	case PLAYER:
	{
		this->Set_Dead();
		MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtleDead>::Create(m_tInfo.fX, m_tInfo.fY));
	}
	break;
	case ITEM:
	{
		break;
	}
	default:
		break;
	}
}

