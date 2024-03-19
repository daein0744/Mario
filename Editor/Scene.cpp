#include "stdafx.h"
#include "Scene.h"
#include "Obj.h"
#include "Player.h"

CScene::CScene()
{
    
}

CScene::~CScene()
{
    Release();
}

void CScene::AddObject(int ObjID, CObj* NewObj)
{
    m_GameObjectList[ObjID].push_back(NewObj);
}

void CScene::RemoveObject(int ObjID, CObj* NewObj)
{
    for (auto it = m_GameObjectList[ObjID].begin(); it != m_GameObjectList[ObjID].end(); )
    {
        if (NewObj == (*it))
        {
            if (*it)
                Safe_Delete(*it);
            it = m_GameObjectList[ObjID].erase(it);
        }
        else
        {
            it++;
        }       
    }
}


void CScene::Initialize()
{
    for (int i = 0; i < OBJ_END; i++)
    {
        for (auto item : m_GameObjectList[i])
        {
            if (item)
                item->Initialize();
        }
    }

}

void CScene::Update()
{
    for (int i = 0; i < OBJ_END; i++)
    {
        for (auto it = m_GameObjectList[i].begin(); it != m_GameObjectList[i].end(); )
        {
            int isDead = (*it)->Update();
            if (isDead == OBJ_DEAD)
            {
                Safe_Delete(*it);
                it = m_GameObjectList[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void CScene::Late_Update()
{
    for (int i = 0; i < OBJ_END; i++)
    {
        for (auto item : m_GameObjectList[i])
        {
            if (item)
                item->Late_Update();
        }
    }
}

void CScene::Render(HDC hDC)
{
    for (int i = 0; i < OBJ_END; i++)
    {
        for (auto item : m_GameObjectList[i])
        {
            if (item)
                item->Render(hDC);
        }
    }
}

void CScene::Release()
{
    for (int i = 0; i < OBJ_END; i++)
    {
        for (auto it = m_GameObjectList[i].begin(); it != m_GameObjectList[i].end(); )
        {
            Safe_Delete(*it);
            it = m_GameObjectList[i].erase(it);
        }
    }
}
