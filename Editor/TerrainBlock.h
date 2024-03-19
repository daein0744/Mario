#pragma once
#include "Block.h"

class CTerrainBlock : public CBlock
{
public:
	CTerrainBlock(bool bIsActive, BLOCKID blockID,
		WORLDID worldID, INFO info);
	virtual ~CTerrainBlock();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	virtual void Hit_Up()			override;
	virtual void Hit_Down()			override;
	virtual void Hit_LeftRight()	override;
};

