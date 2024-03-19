#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	m_CurScene->Initialize();
}

void CSceneMgr::Release()
{
	for (auto it = m_SceneList.begin(); it != m_SceneList.end(); )
	{
		if (it->second)
		{
			it->second->Release();
			Safe_Delete((it->second));
		}
		it = m_SceneList.erase(it);	
	}
}

void CSceneMgr::Update()
{
	if (m_CurScene)
		m_CurScene->Update();
}

void CSceneMgr::Late_Update()
{
	if (m_CurScene)
		m_CurScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_CurScene)
		m_CurScene->Render(hDC);
}

void CSceneMgr::AddScene(string name, CScene* newScene)
{
	m_SceneList.insert({ name,newScene });
}

void CSceneMgr::SelectScene(string name)
{
	m_CurScene = m_SceneList[name];
	Initialize();
}

void CSceneMgr::RemoveScene(string name)
{
	m_SceneList.erase(name);
}
