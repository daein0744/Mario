#include "stdafx.h"
#include "KoopaFire.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
CKoopaFire::CKoopaFire()
{
}


CKoopaFire::~CKoopaFire()
{
	Release();
}

void CKoopaFire::Initialize(void)
{
	m_tInfo.fCX = 48;
	m_tInfo.fCY = 16;
	m_fSpeed = 5.f;

	MBITMAP->Insert_Bmp(L"../Image/Monster/Koopa_Attack.bmp", L"Koopa_Attack");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CKoopaFire::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	m_tInfo.fX -= m_fSpeed;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CKoopaFire::Late_Update(void)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();

	if (m_tRect.left + iScrollX + Player_Speed< 0 || m_tRect.right + iScrollX + Player_Speed> WINCX ||
		m_tRect.top < 0 || m_tRect.bottom > WINCY)
		m_bDead = OBJ_DEAD;
	__super::Move_Frame();
}

void CKoopaFire::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Koopa_Attack");
	GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
		int(m_tRect.left + iScrollX + Player_Speed), // 복사 받을 텍스처 위치 좌표 X
		int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
		int(m_tInfo.fCX), // 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 텍스처 세로 사이즈
		hMemDC,	// 복사할 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 12),	// 비트맵 출력 좌표 X
		m_tFrame.iMotion * int(m_tInfo.fCY),	// 비트맵 출력 좌표 Y
		int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상
}

void CKoopaFire::Release(void)
{
}
