#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float	Get_ScrollX(void) { return m_fScrollX; }
	void	Set_ScrollX(float _fX) { m_fScrollX += _fX; }

public:
	static CScrollMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
};

