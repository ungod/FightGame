#pragma once
#include "cocos2d.h"
#include "../Skill.h"
#include "../SkillProperty.h"
USING_NS_CC;
using namespace std;

class SkillAttack: public Object
{
public:
    
    SkillAttack();
    ~SkillAttack();
    
    static SkillAttack* create(SkillProperty* skillProperty);
    bool initWithSkillProperty(SkillProperty* skillProperty);
    


    CC_SYNTHESIZE_RETAIN(Skill*, m_skill, Skill);
    CC_SYNTHESIZE(float, m_attackRate, AttackRate);
    
};
