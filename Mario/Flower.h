#pragma once
#include "Item.h"
#include "Define.h"

class CFlower
	: public CItem
{
	enum STATE { IDLE, SPARKLING, STATE_END };

public:
	CFlower();
	virtual ~CFlower();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Key_Input();
	void Motion_Change();
	void Flower_Dead();

private:
	STATE	m_eCurState;
	STATE	m_ePreState;
};