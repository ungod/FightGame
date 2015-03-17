#pragma once
#include "cocos2d.h"
#include "Sprites/BaseSprites/SimpleAnimation.h"

USING_NS_CC;

using namespace std;

/*碰撞框中的显示动画*/

class ContactAnimateSprite : public SimpleAnimation
{
public:
	ContactAnimateSprite();
	~ContactAnimateSprite(void);
    static ContactAnimateSprite* create(const char *name);
    bool init(const char *name);
    virtual void playNewAnimation(string aniamtionName);//播放新的动画,动画结束自动消亡
    virtual void onAnimationFinished() override;
    ContactAnimateSprite* clone();//克隆
    
    virtual void onStarted();
    virtual void onFinshed();//消亡
    //virtual void
    
    //@brief 运行时的动画名称
	CC_SYNTHESIZE(string, m_idleAnimation, IdleAnimation);
    
    //@brief 消亡动画
    CC_SYNTHESIZE(string, m_disappearAnimationAnimationm, DisappearAnimationAnimation);
    
    //@消亡音效
    CC_SYNTHESIZE(int, m_disappearMusicID, DisappearMusicID);
};
