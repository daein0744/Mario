#include "stdafx.h"
#include "Koopa.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BlockMgr.h"
#include "AbstractFactory.h"

CKoopa::CKoopa()
{
}


CKoopa::~CKoopa()
{
	Release();
}

void CKoopa::Initialize(void)
{
	m_tInfo = {1700.f, 300.f, 64.f,64.f};
	m_fSpeed = 5.f;

	MBITMAP->Insert_Bmp(L"../Image/Monster/Koopa_Move.bmp", L"Koopa_Move");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500;
	m_tFrame.dwTime = GetTickCount();

	m_fTime = 0;
	m_fPower = 5;
	m_dwTime = GetTickCount();
}

int CKoopa::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (rand() % 50 == 5)
	{
		MOBJ->AddObject(MONSTER, CAbstractFactory<CKoopaFire>::Create(m_tInfo.fX - 10, m_tInfo.fY + 20));
	}

	Move();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CKoopa::Late_Update(void)
{

	__super::Move_Frame();
}

void CKoopa::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Koopa_Move");
	GdiTransparentBlt(hDC,		// 복사 받을 최종 DC
		int(m_tRect.left + iScrollX + Player_Speed), // 복사 받을 텍스처 위치 좌표 X
		int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
		int(m_tInfo.fCX), // 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 텍스처 세로 사이즈
		hMemDC,	// 복사할 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 16),	// 비트맵 출력 좌표 X
		m_tFrame.iMotion * int(m_tInfo.fCY),	// 비트맵 출력 좌표 Y
		int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상
}

void CKoopa::Release(void)
{
}


void CKoopa::Move()
{
	m_fTime += 0.2f;
	

	if (m_dwTime + 1500 < GetTickCount())
	{
		m_fPower = 8;
		m_fTime = 0;
		m_tInfo.fY -= 5;
		m_dwTime = GetTickCount();
	}

	float	fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// 충돌하면 -1 곱하기

	
	if (m_fPower > 0)
	{
		m_tInfo.fY -= m_fPower * m_fTime - (4.f * m_fTime * m_fTime) * 0.5f;
		if (bBlockCol)
		{
			m_fPower = 0;
			m_fTime = 0;
			m_tInfo.fY = fY - m_tInfo.fCY * 0.5f + 1;
		}
	}
}