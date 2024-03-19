#include "stdafx.h"
#include "QuestionBlock.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"

CQuestionBlock::CQuestionBlock(bool bIsActive, BLOCKID blockID,
	WORLDID worldID, INFO info) :
	CBlock(bIsActive, blockID, worldID, info)
{
}

CQuestionBlock::~CQuestionBlock()
{
}

void CQuestionBlock::Initialize(void)
{
}

int CQuestionBlock::Update(void)
{
	return 0;
}

void CQuestionBlock::Late_Update(void)
{
}

void CQuestionBlock::Render(HDC hDC)
{
	HDC		hBackDC;
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
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"TerrainOverWorld");
		break;
	}

	StretchBlt(
		hDC,
		int(m_tRect.left - x),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hBackDC,
		0,
		0,
		16,
		16,
		SRCCOPY);
}

void CQuestionBlock::Release(void)
{
}

void CQuestionBlock::Hit_Up()
{
}

void CQuestionBlock::Hit_Down()
{
}

void CQuestionBlock::Hit_LeftRight()
{
}
