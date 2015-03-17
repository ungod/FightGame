#pragma once
#include "cocos2d.h"
#include "Sqlite/SqliteResolver.h"
#include "../Skill.h"
//#include "Sprites/Entity/SkillContactSprite.h"
USING_NS_CC;

class AnimationSprite;
class SkillContactSprite;
//技能控制系统,负责管理整个技能,包括子技能


class SkillSystem : public Skill
{
public:
    
    SkillSystem();
    ~SkillSystem();
    static SkillSystem* create(const char* pFile);
    static SkillSystem* create(int ID);
   
    bool initWithID(int ID);
    
    virtual bool initWithSkillResolver(SqliteResolver *resolver) override;//从SkillResolver初始化
    
    //
    virtual SkillSystem* clone() const override;
    
    //@brief 技能启动的时候进行回调
    virtual void onStarted() override;
    
    //@brief 技能播放完毕的时候进行回调
    virtual void onFinished() override;
    
    //@brief 发生碰撞时会调用此函数
    //@param pSender攻击的节点
    //@param pTarget被击中的节点
    virtual void onCollsion(SkillContactSprite* pSender, AnimationSprite* pTarget) override;
    
    
    CC_SYNTHESIZE(Array*, m_skillArray, BulletsArray);
    
    //@brief 删除对象
    virtual void removeSkill(SkillContactSprite* child) override;
    
    //@brief 添加子类对象
    virtual void addSkill(SkillContactSprite* child) override;
    
    
    //@brief 删除所有子类
    virtual void removeSkills() override;

};
