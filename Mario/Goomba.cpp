#include "stdafx.h"
#include "Goomba.h"
#include "BitmapMgr.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CGoomba::CGoomba()
{
}


CGoomba::~CGoomba()
{
	Release();
}

void CGoomba::Initialize(void)
{
	m_tInfo = { 600.f, 100.f, 32.f, 32.f };
	m_fSpeed = 2.f;	

	MBITMAP->Insert_Bmp(L"../Image/Monster/Goomba_Move.bmp", L"Goomba_Move");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500;
	m_tFrame.dwTime = GetTickCount();
}

int CGoomba::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CGoomba::Late_Update(void)
{
	__super::Move_Frame();
}

void CGoomba::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Goomba_Move");
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

void CGoomba::Release(void)
{
}

void CGoomba::Move()
{
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// 충돌하면 -1 곱하기

	m_tInfo.fY += 8.f;
	if (bBlockCol)
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f + 1;
}

void CGoomba::Hit_Up(CObj * _pTarget)
{
	switch (_pTarget->Get_ObjID())
	{
	case PLAYER:
	{
		this->Set_Dead();
		// -> 굼바 죽는 render 뽑아주면됨.
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

