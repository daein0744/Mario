#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#define JUMP_POWER 8.f

#define MINI_MARIO			0
#define ADULT_MARIO			1
#define FLOWER_MARIO		2

CPlayer::CPlayer()
	:m_bJump(false), m_fTime(0.f), m_ePreState(STATE_END), m_eCurState(RIDLE)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 60.f, 500.f, 32.f, 32.f };
	m_eObjID = PLAYER;
	m_fSpeed = 3.f;
	m_fAccel = 5.f;
	m_bMoving = false;
	m_fPower = JUMP_POWER;
	m_bPowerUpState = true;
	m_pFrameKey = MINI_MARIO_RIDLE;
	m_bRunState = false;
	m_iEvloution = 0;
	m_dwTime = GetTickCount();
	__super::Update_Rect();
}

int CPlayer::Update(void)
{
	if (m_iEvloution == 0)
	{
		m_tInfo.fCY = 32.f;
	}
	else if (m_iEvloution == 1)
	{
		m_tInfo.fCY = 64.f;
	}
	else
	{
		m_tInfo.fCY = 64.f;
	}
	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_bRunState)
	{
		if (m_tFrame.dwSpeed > 50.f)
			m_tFrame.dwSpeed -= 2;

		if (m_fSpeed < 6.f)
			m_fSpeed = m_fSpeed + 0.2f;
	}
	else
	{
		m_fSpeed = 3.f;
		m_tFrame.dwSpeed = 200;
	}

	Jumping();
	OffSet();
	Motion_Change();

	__super::Move_Frame();
}

void CPlayer::OffSet(void)
{
	int      iOffSetmaxX = 300;
	int      iScrollX = (int)MSCROLL->Get_ScrollX();

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		MSCROLL->Set_ScrollX(-m_fSpeed);
}

void CPlayer::SelectFrameKey(void)
{
	if (m_eCurState == LIDLE)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_LIDLE;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_LIDLE;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_LIDLE;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_LIDLE;
			break;
		}
	}
	else if (m_eCurState == RIDLE)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_RIDLE;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_RIDLE;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_RIDLE;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_RIDLE;
			break;
		}
	}
	else if (m_eCurState == LRUN)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_LRUN;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_LRUN;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_LRUN;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_LRUN;
			break;
		}
	}
	else if (m_eCurState == RRUN)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_RRUN;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_RRUN;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_RRUN;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_RRUN;
			break;
		}
	}
	else if (m_eCurState == LJUMP)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_LJUMP;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_LJUMP;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_LJUMP;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_LJUMP;
			break;
		}
	}
	else if (m_eCurState == RJUMP)
	{
		switch (m_iEvloution)
		{
		case 0:
			m_pFrameKey = MINI_MARIO_RJUMP;
			break;
		case 1:
			m_pFrameKey = ADULT_MARIO_RJUMP;
			break;
		case 2:
			m_pFrameKey = FLOWER_MARIO_RJUMP;
			break;
		default:
			m_pFrameKey = FLOWER_MARIO_RJUMP;
			break;
		}
	}

}

void CPlayer::Render(HDC hDC)
{
	int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HDC      hMemDC = CBitmapMgr::Get_Instance()->Find_Img(m_pFrameKey);

	//Rectangle(hDC, 200, 200, 300, 300);

	if (m_iEvloution == FLOWER_MARIO)
	{
		cout << m_tFrame.iFrameStart << endl;
		GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
			int(m_tRect.left + iScrollX), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,   // 복사할 DC
			m_tFrame.iFrameStart * int(m_tInfo.fCX + 18.f),   // 비트맵 출력 좌표 X
			m_tFrame.iMotion * int(m_tInfo.fCY + 20.f),   // 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}
	else
	{
		GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
			int(m_tRect.left + iScrollX), // 복사 받을 텍스처 위치 좌표 X
			int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
			int(m_tInfo.fCX), // 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 텍스처 세로 사이즈
			hMemDC,   // 복사할 DC
			m_tFrame.iFrameStart * int(m_tInfo.fCX + 28.f),   // 비트맵 출력 좌표 X
			m_tFrame.iMotion * int(m_tInfo.fCY + 28.f),   // 비트맵 출력 좌표 Y
			int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
			int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}

}

void CPlayer::Release(void)
{
}

void CPlayer::Hit(CObj * _pTarget)
{
}

void CPlayer::Hit_Up(CObj * _pTarget)
{
}

void CPlayer::Hit_Down(CObj * _pTarget)
{
	switch (_pTarget->Get_ObjID())
	{
	case MONSTER:
	{
		m_fTime = 0;
		m_fPower = JUMP_POWER + 3;
		break;
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

void CPlayer::Hit_LeftRight(CObj * _pTarget)
{
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case LIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 120;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 120;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LJUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RJUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		default:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}

}

void CPlayer::Key_Input(void)
{
	float fY = 0.f;
	if (m_dwTime + 200 < GetTickCount())
	{
		if (MKEY->Key_Pressing('A'))
		{
			MOBJ->AddObject(BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY));
		}
		m_dwTime = GetTickCount();
	}

	if (MKEY->Key_Pressing(VK_LEFT))
	{
		float x = MSCROLL->Get_ScrollX();
		if (m_tRect.left + x  > 0.f)
			m_tInfo.fX -= m_fSpeed;

		m_eCurState = LRUN;
		SelectFrameKey();

	}
	else if (MKEY->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = RRUN;
		SelectFrameKey();
	}

	if (MKEY->Key_Up(VK_LEFT))
	{
		m_eCurState = LIDLE;
		SelectFrameKey();
	}
	if (MKEY->Key_Up(VK_RIGHT))
	{
		m_eCurState = RIDLE;
		SelectFrameKey();
	}

	if (MKEY->Key_Pressing('Z'))
	{
		if (MKEY->Key_Pressing(VK_LEFT))
		{
			m_eCurState = LJUMP;
			SelectFrameKey();
		}
		else if (MKEY->Key_Pressing(VK_RIGHT))
		{
			m_eCurState = RJUMP;
			SelectFrameKey();
		}
		else if (MKEY->Key_Up(VK_LEFT))
		{
			m_eCurState = LJUMP;
			SelectFrameKey();
		}
		else if (MKEY->Key_Up(VK_RIGHT))
		{
			m_eCurState = RJUMP;
			SelectFrameKey();
		}


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
	



	if (MKEY->Key_Pressing('X'))
	{
		m_bRunState = true;
	}

	if (MKEY->Key_Up('X'))
	{
		m_bRunState = false;
	}


}
void CPlayer::Jumping(void)
{
	// 블록 충돌처리 추가
	if (m_bJump)
	{
		float value = m_fPower * m_fTime - (6.8f * m_fTime * m_fTime) *0.55f;
		if (value < -15.f)
			value = -15.f;
		m_tInfo.fY -= value;

		m_fTime += 0.2f;
		/*m_tInfo.fY -= m_fPower * m_fPressingTime - (9.8f * m_fPressingTime * m_fPressingTime) * 0.5f;*/
	}
	else
		m_tInfo.fY += 10.f;

}


void CPlayer::HitBlock_Up(CBlock * _pTarget)
{
	BLOCKID eID = _pTarget->GetBlockID();
	switch (eID)
	{
	case BrickBlock:
	{
		m_tInfo.fY = _pTarget->Get_Rect().top - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_fPower = JUMP_POWER;
		m_fTime = 0.f;
		m_bPowerUpState = true;
	}

	break;
	case QuestionBlock:
		m_tInfo.fY = _pTarget->Get_Rect().top - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_fPower = JUMP_POWER;
		m_fTime = 0.f;
		m_bPowerUpState = true;
		break;
	case TerrainBlock:
		m_tInfo.fY = _pTarget->Get_Rect().top - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_fPower = JUMP_POWER;
		m_fTime = 0.f;
		m_bPowerUpState = true;
		break;
	default:
		break;
	}
}

void CPlayer::HitBlock_Down(CBlock * _pTarget)
{
	BLOCKID eID = _pTarget->GetBlockID();
	switch (eID)
	{
	case BrickBlock:
	{
		m_fTime += 4.f;
	}
	break;
	case QuestionBlock:
		m_fTime += 4.f;
		break;
	case TerrainBlock:
		m_fTime += 4.f;
		break;
	default:
		break;
	}
}

void CPlayer::HitBlock_LeftRight(CBlock * _pTarget)
{
}
