#include "stdafx.h"
#include "BrickBlock.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "BlockMgr.h"

CBrickBlock::CBrickBlock(bool bIsActive, BLOCKID blockID,
	WORLDID worldID, INFO info) :
	CBlock(bIsActive, blockID, worldID, info)
{
}

CBrickBlock::~CBrickBlock()
{
}

void CBrickBlock::Initialize(void)
{
}

int CBrickBlock::Update(void)
{
	return 0;
}

void CBrickBlock::Late_Update(void)
{
}

void CBrickBlock::Render(HDC hDC)
{
	HDC		hBackDC; 
	int x = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eWorldID)
	{
	case OverWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"BrickOverWorld");
		break;
	case UnderWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"BrickUnderWorld");
		break;
	case BossWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"BrickBossWorld");
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

void CBrickBlock::Release(void)
{
}

void CBrickBlock::Hit_Up()
{
}

void CBrickBlock::Hit_Down()
{
}

void CBrickBlock::Hit_LeftRight()
{
}
