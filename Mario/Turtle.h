#pragma once
#include "Monster.h"
#include "TurtleDead.h"
class CTurtle : public CMonster
{
public:
	CTurtle();
	virtual ~CTurtle();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

	virtual void Move();

	virtual void Hit_Up(CObj * _pTarget);
};

