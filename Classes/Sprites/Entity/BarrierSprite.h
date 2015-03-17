#pragma once
#include "ItemSprite.h"

class BarrierSprite : public ItemSprite
{
public:
	BarrierSprite();
	~BarrierSprite();

	static BarrierSprite* create();

	virtual void setDataParam();
	virtual void onCollsion(AnimationSprite* pTarget);
};