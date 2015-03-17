#pragma once
#include "ItemSprite.h"
#include "Sprites/Role/Hero.h"

class DungeonPortal : public AnimationSprite
{
public:
	DungeonPortal();
	~DungeonPortal();

	static DungeonPortal* create();

	CC_SYNTHESIZE(Hero*, m_target, Target);
	CC_SYNTHESIZE(int, m_dungeonID, DungeonID);

protected:
	virtual bool init();
	virtual void update(float delta);
};