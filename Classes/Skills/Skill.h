#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <Box2D/Box2D.h>
#include "Sqlite/SqliteResolver.h"
#include "Music/MusicPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


class AnimationSprite;
class SkillSystem;
class SkillItem;
class SkillContactSprite;

class Skill : public Object
{
public:
    
    Skill();
    ~Skill();
    
    enum HurtJudgement{HurtAndInterrupt, HurtWithoudInterrupt, NoHurt};
    

    //@brief 克隆
    virtual Skill* clone() const = 0;
    
    //@brief 技能启动的时候进行回调
    virtual void onStarted() = 0;
    
    //@brief 技能生命结束的时候进行回调
    virtual void onFinished() = 0;
    
    //@brief 发生碰撞时会调用此函数
    //@param pSender攻击的节点
    //@param pTarget被击中的节点
    virtual void onCollsion(SkillContactSprite* pSender, AnimationSprite* pTarget) = 0;
    
    
    //@brief 添加子类对象
    virtual void addSkill(SkillContactSprite* child) = 0;
    
    //@brief 当技能中存在多个伤害框或者攻击对象的时候,就存在自对象这一说法
    //发生碰撞的时候我们仅仅需要移除一个
    //@param  要删除的攻击对象
    virtual void removeSkill(SkillContactSprite* child) = 0;
    
    //@brief 删除所有子类
    virtual void removeSkills() = 0;
    
    /*启动技能
     @param pTarget 使用的技能的拥有者
     @param name 保留用
     *param direction 技能运动的方向
       direction.x > 0 向右
       direction.x < 0 向左
     
     */
    virtual void startSkillWithOwner(AnimationSprite* pOwner, Point direction);
    
 
    /*技能发放完毕的回调
     @param pTarget 接收回调的实例
     @param callFunc 调用函数的名称
     */
    virtual void setFinishedCallback(Node* pTarget, SEL_CallFuncO selector);
    virtual bool initWithSkillResolver(SqliteResolver *resolver);//从SkillResolver初始化

    CC_SYNTHESIZE_RETAIN(SqliteResolver*, m_resolver, SkillResolver);
    
    
    
    /*设定技能的名称
     *@param m_name技能名称
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_skillName, SkillName);
    
    //是否跟随角色 0 不跟随  1或者其他数字都跟随
    CC_SYNTHESIZE(bool, m_skillFollow, SkillFollow);
    
    
    //技能使用者的动画动作名称
    CC_SYNTHESIZE_PASS_BY_REF(string, m_animationName, AnimationName);
    
    /*设定技能正常的图标
     *@param m_skillIcon正常的图标
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_skillIcon, SkillIcon);
    
    /*设定技能失效的图标
     *@param m_skillIconDisabled失效的图标
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_skillIconDisabled, SkillIconDisabled);

    /*设定技能音效
     *@param m_skillMusic音乐文件
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, m_skillMusicID, SkillMusicID);
    
    //MP消耗值
    CC_SYNTHESIZE(int, m_skillMPConsume, SkillMPConsume);

    //受创判定（释放技能的时候自己的受创表现）（0 受到伤害且被打断  1 受到伤害但不会被打断  2 不会受到伤害
    CC_SYNTHESIZE(int, m_skillHitJudgement, SkillHitJudgement);
    
    //条件状态  (技能使用需要的状态)（0 站立   1  移动  2  站立和移动）
    CC_SYNTHESIZE(int, m_skillCondition, SkillCondition);
    
    //场地限制(不能使用该技能的场地)（0=所有都可以用 1=竞技场  2=副本  3=主城  4=主城和副本）
    CC_SYNTHESIZE(int, m_skillPlace, SkillPlace);
    
    //自动进行攻击的距离判断
    //  AI有效距离X（怪物X轴的技能判定范围）单位：像素  //   AI有效距离Z（怪物Z轴的技能判定范围）单位：像素
    CC_SYNTHESIZE(Point, m_aiDistance, AiDistance);
    
    //@brief 攻击时运动的曲线
    CC_SYNTHESIZE(Sequence*, m_attackMotionCurve, AttackMotionCurve);
    
    /*设定技能的发出者
     *@param m_pOwner 发出技能的使用者
     */    
    CC_SYNTHESIZE(AnimationSprite*, m_pOwner, Owner);
    
    //技能使用者的方向,player当前面朝向x:大于0为向右,小于0为向左  y:大于0向上,小于0向下
    CC_SYNTHESIZE(Point, m_direction, Direction);
    

    //@brief 技能按钮的指针
    //@param m_skillItem 技能菜单上的按钮
    CC_SYNTHESIZE(SkillItem*, m_skilItem, SkillItem);
    
    
protected:
    SEL_CallFuncO m_pFuncSelector;
    Node* m_callbackTarget;
    
    
    
};
