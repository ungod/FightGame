#pragma once
#include "cocos2d.h"
#include "Sqlite/SqliteResolver.h"

USING_NS_CC;
USING_NS_CC_EXT;


class AnimationSprite;
class SkillSystem;
class SkillItem;
class SkillContactSprite;

class SkillProperty : public Object
{
public:
    static SkillProperty* create(int ID);
    SkillProperty();
    ~SkillProperty();
    
    bool initWithID(int ID);
    
    
    CC_SYNTHESIZE(int, m_MPConsume, MPConsume);
    CC_SYNTHESIZE(int, m_skillID, SkillID);
    
};
