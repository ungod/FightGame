#pragma once
#include "cocos2d.h"
#include "SkillItem.h"
USING_NS_CC;

class Bullets;

enum e_skillButton{e_skillBtattack = 120, e_skillBt0};

class SkillHudLayer : public Layer
{
public:
    SkillHudLayer();
    ~SkillHudLayer();
    CREATE_FUNC(SkillHudLayer);
    bool init();
    bool initItems(Point center);
    SkillItem* getSkillButton( int index);
    
    virtual void onAttack();
    virtual void onSkill(Object* selectedItem);
    
    CC_SYNTHESIZE_READONLY(Menu*, m_skillMenu, SkillMenu);
    CC_SYNTHESIZE_READONLY(SkillItem*, m_attackItem, AttackItem);
    
    CC_SYNTHESIZE(int, m_skillID, SkillID);//技能文件
    CC_SYNTHESIZE(bool, m_itemVisible, ItemVisible);//是否可见
    CC_SYNTHESIZE(Point, m_itemPosition, ItemPosition);
    CC_SYNTHESIZE(float, m_skillCDTime, SkillCDTime);//技能冷却时间
};
