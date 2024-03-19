#pragma once
#include "Obj.h"

enum BLOCKID
{
	QuestionBlock, BrickBlock, TerrainBlock, BlockEnd
};

enum WORLDID
{
	OverWorld, UnderWorld, BossWorld, WorldEnd
};

class CBlock : public CObj
{
public:
	CBlock() {}
	CBlock(bool bIsActive, BLOCKID blockID,
		WORLDID worldID, INFO info);
	virtual ~CBlock();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	// 상충돌
	virtual void HitBlock_Up(CObj* _pObj) {}
	// 하충돌
	virtual void HitBlock_Down(CObj* _pObj) {}
	// 좌우충돌
	virtual void HitBlock_LeftRight(CObj* _pObj) {}

protected:
	bool m_bIsActive;
	BLOCKID m_eBlockID;
	WORLDID m_eWorldID;

public:
	void	SetActive(bool state)		{ m_bIsActive = state; }
	bool	GetActive() const			{ return m_bIsActive; }
	BLOCKID GetBlockID() const			{ return m_eBlockID; }
	void	SetBlockID(BLOCKID blockID) { m_eBlockID = blockID; }
	WORLDID GetWorldID() const			{ return m_eWorldID; }
	void	SetWorldID(WORLDID worldID) { m_eWorldID = worldID; }
};

