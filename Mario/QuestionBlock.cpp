#include "stdafx.h"
#include "QuestionBlock.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CQuestionBlock::CQuestionBlock(bool bIsActive, BLOCKID blockID,
	WORLDID worldID, INFO info) :
	CBlock(bIsActive, blockID, worldID, info)
{
	m_bDead = OBJ_NOEVENT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 150;
	m_tFrame.dwTime = GetTickCount();
}

CQuestionBlock::~CQuestionBlock()
{
}

void CQuestionBlock::Initialize(void)
{
}

int CQuestionBlock::Update(void)
{

	return OBJ_NOEVENT;
}

void CQuestionBlock::Late_Update(void)
{
	Move_Frame();
}

void CQuestionBlock::Render(HDC hDC)
{
	HDC      hBackDC;
	int x = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eWorldID)
	{
	case OverWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"QuestionOverWorld");
		break;
	case UnderWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"QuestionUnderWorld");
		break;
	case BossWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"QuestionOverWorld");
		break;
	default:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"QuestionOverWorld");
		break;
	}
	if (m_bDead)
	{
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"ItemBlock_inactive");
		m_tFrame.iFrameStart = 0;
	}

	GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
		int(m_tRect.left + x), // 복사 받을 텍스처 위치 좌표 X
		int(m_tRect.top), // 복사 받을 텍스처 위치 좌표 Y
		int(m_tInfo.fCX), // 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 텍스처 세로 사이즈
		hBackDC,   // 복사할 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX + 4.f),   // 비트맵 출력 좌표 X
		m_tFrame.iMotion * int(m_tInfo.fCY + 4.f),   // 비트맵 출력 좌표 Y
		int(m_tInfo.fCX), // 복사할 비트맵 텍스처 가로 사이즈
		int(m_tInfo.fCY), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(255, 255, 255)); // 제거할 픽셀 색상
}

void CQuestionBlock::Release(void)
{
}

void CQuestionBlock::HitBlock_Up(CObj * pObj)
{
	int iRandValue = 0;
	switch (pObj->Get_ObjID())
	{
	case PLAYER:
		iRandValue = rand() % 3;
		iRandValue = 2;
		if (0 == iRandValue)
			MOBJ->AddObject(ITEM, CAbstractFactory<CCoin>::Create(
				this->Get_Info().fX,
				this->Get_Info().fY - 32.f));
		else if (1 == iRandValue)
			MOBJ->AddObject(ITEM, CAbstractFactory<CFlower>::Create(
				this->Get_Info().fX,
				this->Get_Info().fY));
		else if (2 == iRandValue)
			MOBJ->AddObject(ITEM, CAbstractFactory<CMushroom>::Create(
				this->Get_Info().fX,
				this->Get_Info().fY - 32.f));
		MBITMAP->Insert_Bmp(L"../Image/Item/ItemBlock_inactive.bmp", L"ItemBlock_inactive");
		m_bDead = OBJ_DEAD;
		break;
	default:
		
		break;
	}
}

void CQuestionBlock::HitBlock_Down(CObj * pObj)
{

}

void CQuestionBlock::HitBlock_LeftRight(CObj * pObj)
{
}