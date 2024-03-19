#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
	enum STATE { IDLE, SPARKLING, STATE_END };

public:
	CItem();
	virtual ~CItem();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	ITEMID		m_eItemId;
};

