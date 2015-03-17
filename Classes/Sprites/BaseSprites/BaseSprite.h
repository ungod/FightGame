#pragma once
#include "cocos2d.h"
#include "../AnimateBase/AnimateAction.h"
#include "../AnimateBase/AnimateData.h"
#include "../BaseSprites/SimpleAnimation.h"
USING_NS_CC;
using namespace std;


/**********
 *精灵角色的基类
 *作用:由于使用的需要,经常要用到帧动画,骨骼动画(Spine和Armature)等
 *为了方便使用,过次类进行动画动作的归纳,是非物理相关的,只涉及动作
 *实现数据(AnimateData)和动作(AnimateAction)分离
 *****************/
class AnimateData;
class AnimateAction;
class ContactSprite;
class Skill;

class BaseSprite : public AnimateData, public AnimateAction
{
public:
    BaseSprite();
	~BaseSprite();
    
    
    
    //测试是否可以进行碰撞
     virtual bool canCollide(ContactSprite* contactSprite);
     virtual void onSkillAnimationFinished();//技能动画播放完成
     virtual void onAttackAnimationFinished();//普通攻击动画播放完成
     virtual void onRemoved();//角色在将要被移除的时候调用;
     virtual void runSkill(Skill* pSkill);
    
    CC_SYNTHESIZE(bool, m_active, Active);
    
    
protected:
    int m_collisionNum;//发生碰撞的次数
    ContactSprite* m_contactSprite;//上次发生碰撞的精灵

};




