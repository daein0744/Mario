#pragma once
#include "Block.h"
#include "Item.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"
class CQuestionBlock : public CBlock
{
public:
	CQuestionBlock(bool bIsActive, BLOCKID blockID,
		WORLDID worldID, INFO info);
	virtual ~CQuestionBlock();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	virtual void HitBlock_Up(CObj*)         override;
	virtual void HitBlock_Down(CObj*)      override;
	virtual void HitBlock_LeftRight(CObj*)   override;
};

