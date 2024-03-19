#pragma once
#include "Define.h"
#include "LogoScene.h"
#include "MenuScene.h"

class CScene;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void   Scene_Change(SCENEID eID);
	void   Update();
	void   Late_Update();
	void   Render(HDC hDC);
	void   Release();

	CScene* GetCurScene() { return m_pScene; }
	SCENEID GetCurSceneID() { return m_eCurScene; }

public:
	static CSceneMgr*   Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void   Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*      m_pInstance;
	CScene*               m_pScene;
	SCENEID               m_eCurScene;
	SCENEID               m_ePreScene;
};

#define MSCENE      CSceneMgr::Get_Instance()