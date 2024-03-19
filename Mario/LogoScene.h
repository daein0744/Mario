#pragma once
#include "Scene.h"
class CLogoScene : public CScene
{
public:
	CLogoScene();
	virtual ~CLogoScene();

public:
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();
};

