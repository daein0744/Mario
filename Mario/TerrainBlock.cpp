#include "stdafx.h"
#include "TerrainBlock.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"

CTerrainBlock::CTerrainBlock(bool bIsActive, BLOCKID blockID,
	WORLDID worldID, INFO info) :
	CBlock(bIsActive, blockID, worldID, info)
{
}

CTerrainBlock::~CTerrainBlock()
{
}

void CTerrainBlock::Initialize(void)
{
}

int CTerrainBlock::Update(void)
{
    return 0;
}

void CTerrainBlock::Late_Update(void)
{
}

void CTerrainBlock::Render(HDC hDC)
{
	HDC		hBackDC;
	int x = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eWorldID)
	{
	case OverWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"TerrainOverWorld");
		break;
	case UnderWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"TerrainUnderWorld");
		break;
	case BossWorld:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"TerrainBossWorld");
		break;
	default:
		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"TerrainOverWorld");
		break;
	}

	StretchBlt(
		hDC,
		int(m_tRect.left + x),
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

void CTerrainBlock::Release(void)
{
}
void CTerrainBlock::HitBlock_Up(CObj * pObj)
{
}

void CTerrainBlock::HitBlock_Down(CObj * pObj)
{
}

void CTerrainBlock::HitBlock_LeftRight(CObj * pObj)
{
}