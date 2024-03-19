#include "stdafx.h"
#include "Bullet.h"
#include "BlockMgr.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CBullet::CBullet() : CObj(), m_fDirY(1.f), m_dwTime(GetTickCount()), m_bStart(false)
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo = { 60.f, 100.f, 16.f, 16.f };
	m_eObjID = BULLET;
	m_fSpeed = 5.f;
	m_pFrameKey = MINI_MARIO_RIDLE;
	MBITMAP->Insert_Bmp(L"../Image/Mario/Fireball.bmp", L"Fireball");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
	__super::Update_Rect();
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY += m_fSpeed * m_fDirY;
	if (m_bStart && m_dwTime + 100 < GetTickCount())
	{
		m_fDirY *= -1.f;
		m_dwTime = GetTickCount();
		m_bStart = false;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	__super::Move_Frame();
}

void CBullet::Render(HDC hDC)
{
	int iScrollX = (int)MSCROLL->Get_ScrollX();
	float Player_Speed = (*MOBJ->GetObjList(PLAYER)).front()->Get_Speed();
	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Fireball");
	GdiTransparentBlt(hDC,		// ���� ���� ���� DC
		int(m_tRect.left + iScrollX + Player_Speed), // ���� ���� �ؽ�ó ��ġ ��ǥ X
		int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		int(m_tInfo.fCX), // �ؽ�ó ���� ������
		int(m_tInfo.fCY), // �ؽ�ó ���� ������
		hMemDC,	// ������ DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 8),	// ��Ʈ�� ��� ��ǥ X
		m_tFrame.iMotion * int(m_tInfo.fCY),	// ��Ʈ�� ��� ��ǥ Y
		int(m_tInfo.fCX), // ������ ��Ʈ�� �ؽ�ó ���� ������
		int(m_tInfo.fCY), // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����
}

void CBullet::Release(void)
{
}

void CBullet::HitBlock_Up(CBlock * _pTarget)
{
	m_fDirY *= -1.f;
	m_dwTime = GetTickCount();
	m_bStart = true;


}

void CBullet::HitBlock_Down(CBlock * _pTarget)
{

}

void CBullet::HitBlock_LeftRight(CBlock * _pTarget)
{
}
