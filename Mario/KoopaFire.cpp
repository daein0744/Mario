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
	GdiTransparentBlt(hDC,		// ���� ���� ���� DC
		int(m_tRect.left + iScrollX + Player_Speed), // ���� ���� �ؽ�ó ��ġ ��ǥ X
		int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		int(m_tInfo.fCX), // �ؽ�ó ���� ������
		int(m_tInfo.fCY), // �ؽ�ó ���� ������
		hMemDC,	// ������ DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 12),	// ��Ʈ�� ��� ��ǥ X
		m_tFrame.iMotion * int(m_tInfo.fCY),	// ��Ʈ�� ��� ��ǥ Y
		int(m_tInfo.fCX), // ������ ��Ʈ�� �ؽ�ó ���� ������
		int(m_tInfo.fCY), // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����
}

void CKoopaFire::Release(void)
{
}
