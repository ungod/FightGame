#include "DungeonPortal.h"
#include "Utils/MiscUtils.h"
#include "Scenes/Game/GameScene.h"

DungeonPortal::DungeonPortal()
{
}

DungeonPortal::~DungeonPortal()
{
}

DungeonPortal* DungeonPortal::create()
{
	DungeonPortal* sp = new DungeonPortal;

	if (sp && sp->init())
	{
		sp->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sp);
	}

	return sp;
}

bool DungeonPortal::init()
{
	SqliteResolver* animateResolver = SqliteResolver::create(TABLE_ANIMATIONS, 2);
	RETURN_FALSE_IF(!animateResolver);

	char* animationName = animateResolver->loadSimpleSprite();
	RETURN_FALSE_IF(!animationName);

	RETURN_FALSE_IF(!initWithAnimateAction(SimpleAnimation::create(animationName)));
    
    return true;
}

void DungeonPortal::update( float delta )
{
	AnimationSprite::update(delta);

	if (m_target)
	{
		Point p = Point(abs(m_target->getX() - getX()), m_target->getZ() - getZ());
		if (p.x < 50 && p.y < 50)
		{
			TransitionScene* pTanScene = CCTransitionZoomFlipX::create(0.8f, GameScene::create(m_dungeonID));
			Director::getInstance()->replaceScene(pTanScene);
		}
	}
}
