#include "SimpleAnimation.h"
#include "Sprites/AnimationSprite.h"
#include "CCArmature/animation/CCProcessBase.h"

SimpleAnimation::SimpleAnimation()
{
    m_father = NULL;

}
  
SimpleAnimation::~SimpleAnimation()
{
   
    
}


SimpleAnimation* SimpleAnimation::create(const char *name)
{
    SimpleAnimation* pRet = new SimpleAnimation();
    if(pRet && pRet->init(name))
    {
        pRet->autorelease();
        return pRet;
    }
    
    else
    {
        delete pRet;
        pRet = NULL;
        
    }
    
    return NULL;
    
}



bool SimpleAnimation::init(const char *name)
{
	bool bRet = false;
	do
	{
        CC_BREAK_IF(!Armature::init(name)) ;
        getAnimation()->MovementEventSignal.connect(this, &SimpleAnimation::animationEvent);
        
        bRet = true;
	} while (0);
    
	return bRet;
}





void SimpleAnimation::animationEvent(Armature *armature, armature::MovementEventType movementType, const char *movementID)
{
	//std::string id = movementID;
	if (movementType == armature::MovementEventType::COMPLETE)
	{
        if(m_father != NULL)
        {
            m_father->onAnimationFinished();
        }
        
        onAnimationFinished();
        
	}
}


void SimpleAnimation::playAnimation(const char* aniamtionName, bool loop)//播放动画
{
    armature::MovementData* movementData = getAnimation()->getAnimationData()->getMovement(aniamtionName);
    if(NULL == movementData)
    {
        return ;
    }
    
    getAnimation()->play(aniamtionName, -1, -1, loop);
}

void SimpleAnimation::onAnimationFinished()
{

}
