#pragma once
#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(void);
	void Release(void);
private:
	HDC			m_hDC;
	DWORD		m_dwTime;
	class CBlock* m_pBlock;
};

