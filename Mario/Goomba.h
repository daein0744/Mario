#pragma once
#include "Monster.h"
class CGoomba : public CMonster
{
public:
	CGoomba();
	virtual ~CGoomba();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
public:
	virtual void Move();

	virtual  void Hit_Up(CObj* _pTarget);
};

