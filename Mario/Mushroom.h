#pragma once
#include "Item.h"
#include "Define.h"

class CMushroom :
	public CItem
{
	enum STATE { IDLE, SPARKLING, STATE_END };

public:
	CMushroom();
	virtual ~CMushroom();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Motion_Change();

private:
	STATE               m_ePreState;
	STATE               m_eCurState;
};
