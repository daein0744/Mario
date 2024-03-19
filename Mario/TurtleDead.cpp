#include "stdafx.h"
#include "TurtleDead.h"
#include "BitmapMgr.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"


CTurtleDead::CTurtleDead()
{
}


CTurtleDead::~CTurtleDead()
{
	Release();
}

void CTurtleDead::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_fSpeed = 0.f;

	MBITMAP->Insert_Bmp(L"../Image/Monster/Turtle_Dead.bmp", L"Turtle_Dead");
}

int CTurtleDead::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Move();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CTurtleDead::Late_Update(void)
{
}

void CTurtleDead::Render(HDC hDC)
{
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Turtle_Dead");
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
		int(m_tRect.left + iScrollX + Player_Speed), // 복사 받을 텍스처 위치 좌표 X
		int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
		int(m_tInfo.fCX), // 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 텍스처 세로 사이즈
		hMemDC,	// 복사할 DC
		0,
		0,
		int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상
}

void CTurtleDead::Release(void)
{
}

void CTurtleDead::Hit_Up(CObj * _pTarget)
{
	switch (_pTarget->Get_ObjID())
	{
	case PLAYER:
	{
		if (m_tInfo.fX > _pTarget->Get_Info().fX)
			m_fSpeed = -8.f;
		else
			m_fSpeed = 8.f;
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

void CTurtleDead::Move()
{
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// 충돌하면 -1 곱하기

	m_tInfo.fY += 8.f;
	if (bBlockCol)
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f + 1;
}

