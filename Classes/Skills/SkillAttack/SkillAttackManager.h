#pragma once
#include "cocos2d.h"
#include "../Skill.h"
#include "SkillAttack.h"
#include "Sqlite/SqliteResolver.h"
USING_NS_CC;
using namespace std;


//各种角色攻击的汇总
//主角时以普通攻击的连击使用
//怪物等非控制类角色使用单个技能


class SkillAttackManager : public Object
{
public:
    
    SkillAttackManager();
    ~SkillAttackManager();
    
    static SkillAttackManager* create(int ID);
    
    bool initWithID(int ID);
    
    //@brief 获取技能序号,连续攻击的时候会根据时间变化,每次调用都会重新计时
    int getSkillIndex();
    
    //@brief 获取SkillAttack中的技能
    Skill* getAttackSkill();
    
    //@获取指定序号的技能, 会发生深层拷贝,技能使用的时候用这个方法
    Skill* getSkillAtIndex(int index);
    
    //@获取指定序号的技能,指针传递,读取技能参数的时候使用
    Skill* getSkillAt(int index);

    //@brief 获取技能总计数
    int getSkillCount();
    
    //更新下次有效的攻击时间
    void updateAttackTime();
 
    
    
    //有效攻击的判断时间
    CC_SYNTHESIZE(double, m_nextAttackTime, NextAttackTime);
    
    //@brief 最后一次攻击的等待时间
    CC_SYNTHESIZE(double, m_skillLastDelay, SkillLastDelay);
    
    //@brief 技能列表
    CC_SYNTHESIZE(Array*, m_skillAttackArray, SkillAttackArray);
    
    
    
private:
    int m_currentIndex;
    
    
};
