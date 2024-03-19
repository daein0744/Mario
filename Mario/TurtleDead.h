#pragma once
#include "Monster.h"
class CTurtleDead :
	public CMonster
{
public:
	CTurtleDead();
	virtual ~CTurtleDead();
public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
public:
	virtual  void Hit_Up(CObj* _pTarget);
	virtual  void Move();
};

