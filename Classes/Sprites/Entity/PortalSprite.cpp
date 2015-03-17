#include "PortalSprite.h"
#include "Scenes/Game/GameScene.h"

PortalSprite::PortalSprite()
{
    m_nextMapID = 0;
	m_collsionManual = false;
}

PortalSprite::~PortalSprite()
{
}

PortalSprite* PortalSprite::createWithID(int ID)
{
	PortalSprite* sp = new PortalSprite;

	if (sp && sp->initWithAnimation(ID, "open"))
	{
		sp->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sp);
	}

	return sp;
}

void PortalSprite::setDataParam()
{
	setBodySize(Size(50, 50));
	setZtolerance(50);
}

void PortalSprite::onCollsion( AnimationSprite* pTarget )
{
	GameScene* scn = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());

	if (scn)
	{
		scn->switchGame(this);
	}
}