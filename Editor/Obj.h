#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual int  Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

public:
	INFO			Get_Info(void) { return m_tInfo; }
	RECT			Get_Rect(void) { return m_tRect; }

	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void			Set_Dead(void) { m_bDead = true; }
	bool			Get_Dead(void) { return m_bDead; }

	void			Set_X(float _fX) { m_tInfo.fX += _fX; }
	void			Set_Y(float _fY) { m_tInfo.fY += _fY; }

protected:
	void		Update_Rect(void);


protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	OBJID		m_eObjID;
	TCHAR*		m_pFrameKey;

	bool		m_bDead;
	float		m_fSpeed;
};

