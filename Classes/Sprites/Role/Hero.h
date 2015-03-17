#pragma once
#include "cocos2d.h"
#include "../AnimationSprite.h"
#include "../../DataInfo/RoleProperty.h"
USING_NS_CC;


//通过手柄控制的角色

class Hero : public AnimationSprite
{
public:
	Hero();
	~Hero(void);
    
    virtual void attack();
    
    static Hero* create(SimpleAnimation* pBaseSprite);
    bool initWithAnimateAction(SimpleAnimation* pAnimationSprite);
    
    
    //@技能列表
    CC_SYNTHESIZE_RETAIN(SkillAttackManager*, m_attackListManager ,AttackListManager);
	
};
