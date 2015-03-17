#pragma once
#include "cocos2d.h"
#include "../Physics/ContactSprite.h"

class ItemSprite : public ContactSprite
{
public:

	static ItemSprite* createWithAnimationID(int ID, string idleAnim, string disappearAnim = "");
	
	virtual bool initWithAnimation(int ID, string idleAnim, string disappearAnim = "");
	virtual void setDataParam();

	virtual void updatePosition(const Point &position);
	virtual void onCollsion(AnimationSprite* pTarget);

	ItemSprite();
	~ItemSprite();
};