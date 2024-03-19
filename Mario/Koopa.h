#pragma once
#include "Monster.h"
#include "KoopaFire.h"
class CKoopa :  public CMonster
{
public:
	CKoopa();
	virtual ~CKoopa();
public:
	void Initialize(void);
	int  Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

	void Move();
private:
	float m_fTime;
	DWORD	m_dwTime;
	float m_fPower;
};

