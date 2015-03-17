#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../AnimateBase/AnimateAction.h"
#include "CCArmature/CCArmature.h"
#include "CCArmature/CCBone.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*角色动作等各种参数
 
 
 
 */

class AnimationSprite;


class SimpleAnimation : public armature::Armature, public sigslot::has_slots<>
{
public:
    SimpleAnimation();
    ~SimpleAnimation();
    static SimpleAnimation* create(const char *name);
    bool init(const char *name);
    
    virtual void onAnimationFinished();
    virtual void playAnimation(const char* aniamtionName, bool loop = false);//播放动画
    void animationEvent(armature::Armature *armature, armature::MovementEventType movementType, const char *movementID);
    
    
    CC_SYNTHESIZE(AnimationSprite*,  m_father, Father);

};




