#pragma once
#include "Scene.h"
class CMenuScene : public CScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	SelectMenu		m_eSelect;
	float			m_fStar;
};

