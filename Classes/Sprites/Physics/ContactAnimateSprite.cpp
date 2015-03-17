#include "ContactAnimateSprite.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "Music/MusicPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;



ContactAnimateSprite::ContactAnimateSprite()
{
  m_idleAnimation = "";
  m_disappearMusicID = 0;
  m_disappearAnimationAnimationm = "";
}

ContactAnimateSprite::~ContactAnimateSprite(void)
{

    
}

ContactAnimateSprite* ContactAnimateSprite::clone()
{
    ContactAnimateSprite* pRet = ContactAnimateSprite::create(getName().c_str());
    return pRet;
}


ContactAnimateSprite* ContactAnimateSprite::create(const char *name)
{
    ContactAnimateSprite* pRet = new ContactAnimateSprite();
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



bool ContactAnimateSprite::init(const char *name)
{
	bool bRet = false;
	do
	{
        CC_BREAK_IF(!SimpleAnimation::init(name));
        
        
        
        bRet = true;
	} while (0);
    
	return bRet;
}





void ContactAnimateSprite::playNewAnimation(string aniamtionName)
{
    ContactAnimateSprite* newAnimation = clone();
    if (newAnimation == NULL)
        return;

    
    newAnimation->playAnimation(aniamtionName.c_str());
    
    if(getParent() != NULL)
    {
        Node* father = DataManager::getInstance()->getGameLayer();
        newAnimation->setPosition(getParent()->getPosition());
        father->addChild(newAnimation,getParent()->getZOrder());
        
    }
    
    
}

void ContactAnimateSprite::onAnimationFinished()
{
    removeFromParent();//消亡动画自动消失
    
}




void ContactAnimateSprite::onStarted()
{
   playAnimation(getIdleAnimation().c_str(), true);

}


void ContactAnimateSprite::onFinshed()//消亡
{
	if (getDisappearAnimationAnimation().length() <= 0)
		return;

    playNewAnimation(getDisappearAnimationAnimation());
    MusicPlayer* musiPlayer = MusicPlayer::getInstance();
    if(musiPlayer != NULL)
    {
        musiPlayer->playEffect(getDisappearMusicID());
    }
}









