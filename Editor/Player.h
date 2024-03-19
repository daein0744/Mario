#pragma once
#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	// CObj을(를) 통해 상속됨
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Key_Input(void);

	void	Jumping(void);
	void	OffSet(void);


private:
	bool					m_bJump;
	float					m_fPower;
	float					m_fTime;
	bool					m_bPowerUpState;
	float					m_fAccel;
	bool					m_bMoving;


};

