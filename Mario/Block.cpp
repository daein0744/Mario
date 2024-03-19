#include "stdafx.h"
#include "Block.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"

CBlock::CBlock(bool bIsActive, BLOCKID blockID,
	WORLDID worldID, INFO info) :
	m_bIsActive(bIsActive)
{
	m_tInfo = info;
	m_eBlockID = blockID;
	m_eWorldID = worldID;
	Update_Rect();
}

CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
}

int CBlock::Update(void)
{
	return 0;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Render(HDC hDC)
{
	/*HDC		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"GroundTile");
	int x = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

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
		SRCCOPY);*/
}

void CBlock::Release(void)
{
}

