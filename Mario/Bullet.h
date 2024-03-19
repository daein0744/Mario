#pragma once

#include "Obj.h"

class CBullet
	: public CObj
{
public:
	CBullet();
	~CBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual  void HitBlock_Up(CBlock * _pTarget);
	virtual  void HitBlock_Down(CBlock * _pTarget);
	virtual  void HitBlock_LeftRight(CBlock * _pTarget);

private:
	float m_fDirY;
	bool  m_bStart;
	DWORD m_dwTime;
};