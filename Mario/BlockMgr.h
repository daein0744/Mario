#pragma once

#include "Block.h"

class CBlockMgr
{
private:
	CBlockMgr();
	~CBlockMgr();
public:
	void Initialize();
	int Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

	bool Collision_Block(CObj* _obj, float* _pfY);

	void		CalculateGrid(int& x, int& y, float fSizeX, float fSizeY, POINT& pt);

	void		Save_File(const TCHAR* pFilePath);
	void		Load_File(const TCHAR* pFilePath);

	WORLDID		GetWorldID() const { return m_eCurWorldID; }
	BLOCKID		GetBlockID() const { return m_eCurBlockID; }

	list<CBlock*>* GetBlockList(BLOCKID _eID) { return &m_BlockList[_eID]; }
private:
	void Mouse_Input();
	void Key_Input();
	void MakeBlock(BLOCKID _eCurBlockID, POINT& pt);
	void EraseBlock(POINT& pt);

private:
	static CBlockMgr*		m_pInstance;
	list<CBlock*>			m_BlockList[BlockEnd];
	BLOCKID					m_eCurBlockID;
	WORLDID					m_eCurWorldID;

public:

	static CBlockMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBlockMgr;
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

#define BLOCK CBlockMgr::Get_Instance()

