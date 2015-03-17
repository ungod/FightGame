#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"
#include "Sprites/Entity/PortalSprite.h"

class GameScene : public cocos2d::Scene
{
public:
	
    static GameScene* create(int ID);
    GameScene(void);
	~GameScene(void);
    
	virtual bool initWithID(int ID);
    virtual void onSkill(Object* pskillItem);
    void switchGame(PortalSprite* pSender);
    
    
	CC_SYNTHESIZE(GameLayer*, m_gameLayer, GameLayer);
	CC_SYNTHESIZE(HudLayer*, m_hudLayer, HudLayer);

	CC_SYNTHESIZE_READONLY(bool, m_bIsClose, IsClose);
};


