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
	GdiTransparentBlt(hDC,		// ���� ���� ���� DC
		int(m_tRect.left + iScrollX + Player_Speed), // ���� ���� �ؽ�ó ��ġ ��ǥ X
		int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		int(m_tInfo.fCX), // �ؽ�ó ���� ������
		int(m_tInfo.fCY), // �ؽ�ó ���� ������
		hMemDC,	// ������ DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 28),	// ��Ʈ�� ��� ��ǥ X
		m_tFrame.iMotion * int(m_tInfo.fCY),	// ��Ʈ�� ��� ��ǥ Y
		int(m_tInfo.fCX), // ������ ��Ʈ�� �ؽ�ó ���� ������
		int(m_tInfo.fCY), // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����
}

void CGoomba::Release(void)
{
}

void CGoomba::Move()
{
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// �浹�ϸ� -1 ���ϱ�

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
		// -> ���� �״� render �̾��ָ��.
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

