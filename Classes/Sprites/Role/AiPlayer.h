#pragma once
#include "cocos2d.h"
#include "Sprites/AnimationSprite.h"
#include "AI/AiModule.h"
USING_NS_CC;


//自动控制的角色
class AiPlayer : public AnimationSprite , public AiModule
{
public:
	AiPlayer();
	~AiPlayer(void);
    
    virtual void attack();
    
    static AiPlayer* create(SimpleAnimation* pBaseSprite);
    bool initWithAnimateAction(SimpleAnimation* pAnimationSprite);
	bool startAiModule();
	void initAccessory();

	virtual void knockout();
    virtual void updateAi(float dt);
    
    AnimationSprite* selectOpponent(Array* roleArray);//帅选攻击对象

private:
	Sprite* m_pMonsterHalo;
	LabelTTF* m_pBossNameSprite;
	SimpleAnimation* m_pDieEffect;
};
