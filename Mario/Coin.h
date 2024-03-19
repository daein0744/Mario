#pragma once
#include "Item.h"
#include "Define.h"

class CCoin :
	public CItem
{
	enum STATE { IDLE, SPARKLING, STATE_END };

public:
	CCoin();
	virtual ~CCoin();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Motion_Change();
	void Moving_UD();

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	bool	m_bStart;
	bool	m_bMove;

	float fY;
	float fDeadLine;
};

