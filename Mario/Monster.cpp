#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
	m_eObjID = MONSTER;
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
}

int CMonster::Update(void)
{	
	
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
}
