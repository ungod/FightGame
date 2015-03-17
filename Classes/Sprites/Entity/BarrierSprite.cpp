#include "BarrierSprite.h"

BarrierSprite::BarrierSprite()
{
}

BarrierSprite::~BarrierSprite()
{
}

BarrierSprite* BarrierSprite::create()
{
	BarrierSprite* sp = new BarrierSprite;

	if (sp && sp->initWithAnimation(1, "fly"))
	{
		sp->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sp);
	}

	return sp;
}

void BarrierSprite::setDataParam()
{
	setBodySize(Size(50, 50));
	setZtolerance(70);
}

void BarrierSprite::onCollsion( AnimationSprite* pTarget )
{
	Point fix(1, 1);

	float vec = getX() - pTarget->getX();
	float vel = pTarget->getVelocity().x;
	if ((vel > 0 && vec >= 0) || (vel < 0 && vec <= 0))
	{
		fix.x = 0;
	}

	vec = getZ() - pTarget->getZ();
	vel = pTarget->getVelocity().y;
	if ((vel > 0 && vec >= 0) || (vel < 0 && vec <= 0))
	{
		fix.y = 0;
	}

	pTarget->setIncFix(fix);
}
