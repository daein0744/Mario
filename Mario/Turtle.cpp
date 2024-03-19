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
	else
	{
		HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Turtle_RMove");
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
}

void CTurtle::Release(void)
{
}

void CTurtle::Move()
{
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;
	bool	bBlockCol = BLOCK->Collision_Block(this, &fY);
	// �浹�ϸ� -1 ���ϱ�

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

