#pragma once

#include "cocos2d.h"
#include "Hud/DirectionPad.h"
#include "Sprites/Role/Hero.h"
#include "../Base/BaseLayer.h"
#include "TileLayers/TileParallaxNode.h"
#include "EntitiesManager.h"

USING_NS_CC;

//主城场景
class MainCityLayer : public BaseLayer
{
public:
	
    static MainCityLayer* create(int ID);
    MainCityLayer(void);
	~MainCityLayer(void);
    
	virtual bool initWithID(int ID);

    
    CC_SYNTHESIZE(Hero*, m_hero, Hero);

	CC_SYNTHESIZE(EntitiesManager*, m_entitiesManager, EntitiesManager);

	void initEntitiesManager();

    
    virtual void onDirectionChanged(Point direction);
	virtual void onKeepDirection(Point direction);
	virtual void onDirectionEnded();
    
};


