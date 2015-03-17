#pragma once
#include "Sprites/Decoration/ShadowSprite.h"
#include "Sprites/AnimationSprite.h"
#include "Hero.h"

class NPCSprite : public AnimationSprite
{
public:
	NPCSprite();
	~NPCSprite();

	static NPCSprite* create(int ID);

	CC_SYNTHESIZE(Hero*, m_target, Target);

protected:
	virtual bool initWithID(int ID);
	virtual void update(float delta);

protected:
	LabelTTF* m_label;
};