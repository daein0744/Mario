#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"

#define JUMP_POWER 8.f

CPlayer::CPlayer()
	:m_bJump(false), m_fTime(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 60.f, 100.f, 60.f, 60.f };
	m_fSpeed = 2.f;
	m_fAccel = 5.f;
	m_bMoving = false;
	m_fPower = JUMP_POWER;
	m_bPowerUpState = true;
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/maja2.bmp", L"Player");
}

int CPlayer::Update(void)
{
	Key_Input();

	if (m_bMoving)
	{
		if (m_fSpeed < 15.f)
			m_fSpeed = m_fSpeed + m_fAccel * 0.016f;
	}	
	else
		m_fSpeed = 2.f;
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Jumping();
	OffSet();

	float		fY = 0.f;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);


}

void CPlayer::OffSet(void)
{
	//int		iOffSetminX = 100;
	int		iOffSetmaxX = 300;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	/*if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);*/

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC		hMemDC = CBitmapMgr::Get_Instance()->Find_Img(L"Player");

	//BitBlt(hDC,		// ���� ���� ���� DC
	//	int(m_tRect.left + iScrollX), // ���� ���� �ؽ�ó ��ġ ��ǥ X
	//	int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
	//	int(m_tInfo.fCX), // �ؽ�ó ���� ������
	//	int(m_tInfo.fCY), // �ؽ�ó ���� ������
	//	hMemDC,	// ������ DC
	//	0,	// ��Ʈ�� ��� ��ǥ X
	//	0,	// ��Ʈ�� ��� ��ǥ Y
	//	SRCCOPY); // ��� ȿ��, �״�� �����Ͽ� ���

	GdiTransparentBlt(hDC,		// ���� ���� ���� DC
		int(m_tRect.left + iScrollX), // ���� ���� �ؽ�ó ��ġ ��ǥ X
		int(m_tRect.top), // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		int(m_tInfo.fCX), // �ؽ�ó ���� ������
		int(m_tInfo.fCY), // �ؽ�ó ���� ������
		hMemDC,	// ������ DC
		0,	// ��Ʈ�� ��� ��ǥ X
		0,	// ��Ʈ�� ��� ��ǥ Y
		int(m_tInfo.fCX), // ������ ��Ʈ�� �ؽ�ó ���� ������
		int(m_tInfo.fCY), // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(255, 255, 255)); // ������ �ȼ� ����

}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	float fY = 0.f;

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_bMoving = true;
		m_tInfo.fX -= m_fSpeed;
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		if (m_tInfo.fX - (m_tInfo.fCX / 2) <= (iScrollX*-1))
		{
			
			m_tInfo.fX = iScrollX * -1.f + (m_tInfo.fCX / 2);
		}
		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}
	else
	{
		m_bMoving = false;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_bMoving = true;
		m_tInfo.fX += m_fSpeed;

		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/

	}
	else
	{
		m_bMoving = false;
	}

	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		//m_fPressingTime += 0.01f;
		if (m_bPowerUpState)
		{
			m_fPower += 0.4f;
			
		}
		
		if (m_fPower >= 20.f)
		{
			m_bPowerUpState = false;
		}
		
		m_bJump = true;	
	}


}
void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - (7.0f * m_fTime * m_fTime) * 0.5f;

		m_fTime += 0.2f;

		/*m_tInfo.fY -= m_fPower * m_fPressingTime - (9.8f * m_fPressingTime * m_fPressingTime) * 0.5f;*/

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY / 2);

			m_fPower = JUMP_POWER;
			m_bPowerUpState = true;
		}
	}
	else if (bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY/2);
	else if (!bLineCol)
	{
		m_tInfo.fY +=  (4.9f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
	}
		
}
