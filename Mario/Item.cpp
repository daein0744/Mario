#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
	m_eObjID = ITEM;
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
}

int CItem::Update(void)
{
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release(void)
{
}
