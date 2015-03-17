#pragma once
#include "../Physics/ContactSprite.h"
#include "Skills/Skill.h"

USING_NS_CC;

class b2Body;
class Skill;
class ContactSprite;
/****
* 技能飞行碰撞类
* 
*
**/

class SkillContactSprite : public ContactSprite
{
public:
    SkillContactSprite();

    static SkillContactSprite* create(int ID);

	virtual void onCollsion(AnimationSprite* pTarget);
    virtual void onStarted();
    
	ContactSprite s;

    //@brief 技能的父类
    CC_SYNTHESIZE(Skill*, m_skillParent, SkillParent);
};




