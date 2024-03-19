#pragma once

class CScene;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

private:
	void Initialize();

public:
	void Release();
	void Update();
	void Late_Update();
	void Render(HDC hDC);

	void AddScene(string name, CScene* newScene);
	void SelectScene(string name);
	void RemoveScene(string name);

public:
	static CSceneMgr* Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

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
	static CSceneMgr* m_pInstance;

private:
	CScene* m_CurScene;
	map<string, CScene*>  m_SceneList;
};

#define MSCENE CSceneMgr::Get_Instance()

