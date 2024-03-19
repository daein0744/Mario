#pragma once
#include "Define.h"
#include "Obj.h"
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
public:
	void AddObject(OBJID eID, CObj* pObj);
	void DeleteObject(OBJID eID);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

	list<CObj*>*	GetObjList(OBJID eID) { return &m_ObjList[eID]; }

private:
	static CObjMgr*		m_pInstance;
	list<CObj*>			m_ObjList[OBJ_END];

public:

	static CObjMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

#define MOBJ			CObjMgr::Get_Instance()