#pragma once
#include "Define.h"
class CObj;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	void			AddObject(int ObjID, CObj* NewObj);
	void			RemoveObject(int ObjID, CObj* NewObj);

public:
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();
	
protected:
	list<CObj*> m_GameObjectList[OBJ_END];

};

