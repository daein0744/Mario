#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
	enum STATE { LIDLE, RIDLE, LRUN, RRUN, LJUMP, RJUMP, STATE_END };
public:

	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual  void Hit(CObj* _pTarget);
	virtual  void Hit_Up(CObj* _pTarget);
	virtual  void Hit_Down(CObj* _pTarget);
	virtual  void Hit_LeftRight(CObj* _pTarget);

	virtual  void HitBlock_Up(CBlock* _pTarget) override;
	virtual  void HitBlock_Down(CBlock* _pTarget) override;
	virtual  void HitBlock_LeftRight(CBlock* _pTarget) override;

	void   SetPower(float _power) { m_fPower = _power; }

	void   Motion_Change(void);
	void   Evolution(void);

private:
	void   Key_Input(void);

	void   Jumping(void);
	void   OffSet(void);
	void   SelectFrameKey(void);


private:
	bool               m_bJump;
	float               m_fPower;
	float               m_fTime;
	bool               m_bPowerUpState;
	float               m_fAccel;
	bool               m_bMoving;
	bool               m_bRunState;

	int                  m_iEvloution;

	STATE               m_eCurState;
	STATE               m_ePreState;
	DWORD				m_dwTime;

};