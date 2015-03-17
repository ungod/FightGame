#pragma once
#include "cocos2d.h"
#include "BaseHitBox.h"
#include "Sprites/AnimationSprite.h"
#include "Sqlite/SqliteResolver.h"
#include "Sprites/Physics/ContactAnimateSprite.h"
USING_NS_CC;
using namespace std;

class HitBox : public BaseHitBox
{
public:
    
    HitBox();
    ~HitBox();
    
    bool initWithID(int ID);
    
    //与角色发生碰撞
    virtual void onCollsion(AnimationSprite* pTarget);
    
    //@brief 伤害框的显示动画
    CC_SYNTHESIZE_RETAIN(ContactAnimateSprite*, m_contactAnimateSprite, ContactAnimateSprite);
    
	//@brief 运行时的动画名称
	CC_SYNTHESIZE(string, m_idleAnimation, IdleAnimation);

	//@brief 消亡动画
	CC_SYNTHESIZE(string, m_disappearAnimationAnimationm, DisappearAnimationAnimation);

protected:
    //@brief 进一步的设置
    void advanceSet();
    
};
