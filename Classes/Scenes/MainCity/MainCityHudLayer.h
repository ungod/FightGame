#pragma once
#include "cocos2d.h"
#include "Hud/DirectionPad.h"


class MainCityHudLayer : public cocos2d::Layer
{
public:
	MainCityHudLayer(void);
	~MainCityHudLayer(void);

	bool init();


	CREATE_FUNC(MainCityHudLayer);
	CC_SYNTHESIZE(DirectionPad*, m_dPad, DPad);
	
    
};
