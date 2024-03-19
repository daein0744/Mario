#pragma once
#include "Scene.h"

class CPlayScene : public CScene
{
public:
	CPlayScene();
	virtual ~CPlayScene();

public:
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();
};

