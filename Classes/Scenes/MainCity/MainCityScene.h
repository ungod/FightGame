#pragma once

#include "cocos2d.h"
#include "MainCityHudLayer.h"
#include "MainCityLayer.h"
#include "EntitiesManager.h"

USING_NS_CC;

//主城场景
class MainCityScene : public cocos2d::Scene
{
public:
	
    static MainCityScene* create(int ID);
    MainCityScene(void);
	~MainCityScene(void);
    
	virtual bool initWithID(int ID);
    
    
    
    CC_SYNTHESIZE(MainCityHudLayer*, m_hudLayer, HudLayer);
    CC_SYNTHESIZE(MainCityLayer*, m_mainCityLayer, MainCityLayer);


};


