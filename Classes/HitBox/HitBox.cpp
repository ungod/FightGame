#include "HitBox.h"
#include "Defines.h"
#include "Music/MusicPlayer.h"


HitBox::HitBox()
{
   m_contactAnimateSprite = NULL;
   m_idleAnimation = "";
   m_disappearAnimationAnimationm = "";
}

HitBox::~HitBox()
{
    CC_SAFE_RELEASE(m_contactAnimateSprite);
}

bool HitBox::initWithID(int ID)
{
    bool bRet = false;
    
    do {
        
        SqliteResolver* resolver = SqliteResolver::create(TABLE_HITBOXES, ID);
        CC_BREAK_IF(!resolver);
        
        setDelayTime(resolver->getFloat("DelayTime"));
        setDuration(resolver->getFloat("Duration"));
        setCollideRate(resolver->getFloat("CollideRate"));
        setHitMaxNum(resolver->getInt("HitMaxNum"));
        setHitSingleMaxNum(resolver->getInt("HitSingleMaxNum"));
        setBodySize(resolver->getSize("BodySize"));
        setZtolerance(resolver->getFloat("Ztolerance"));
        setAppearRegion((BodyRegion::Region)resolver->getInt("AppearRegion"));
        setAppearPosition(resolver->getPoint3D("AppearPositon"));
        setAnimationID(resolver->getInt("AnimationID"));
        setIdleMusicID(resolver->getInt("IdleMusicID"));
        setDisappearMusicID(resolver->getInt("DisappearMusicID"));
        setMotionCurve(resolver->getPoint3DSequance("MotionCurve"));
        setOnCollisionMusicID(resolver->getInt("OnCollisionMusicID"));
        setOnCollisionMotionCurve(resolver->getPoint3DSequance("OnCollisionMotionCurve"));
        setOnCollisionAttackerMotionCurve(resolver->getPoint3DSequance("OnCollisionAttackerMotionCurve"));
        setOnCollisionInjuredMotionCurve(resolver->getPoint3DSequance("OnCollisionInjuredMotionCurve"));
        
        setCollisionAnimationID(resolver->getInt("OnCollisionAnimationID"));
        setCollisionAnimation(resolver->getString("OnCollisionAnimation"));
        setCollisionAnimationRegion((BodyRegion::Region)resolver->getInt("OnCollisionAnimationRegion"));
        setCollisionAnimationPos(resolver->getPoint3D("OnCollisionAnimationPos"));

		setDamageConstantWithAP(resolver->getInt("DamageConstantWithAP"));
		setDamageFactorWithAP(resolver->getInt("DamageFactorWithAP"));
		setDamageConstant(resolver->getInt("DamageConstant"));
		setDamageFactor(resolver->getInt("DamageFactor"));

		if(getAnimationID() > 0)
		{
			setIdleAnimation(resolver->getString("IdleAnimation"));
			setDisappearAnimationAnimation(resolver->getString("DisappearAnimation"));
		}
        advanceSet();
        
        bRet = true;
    } while (0);
    
    
    
    return bRet;
}


void HitBox::advanceSet()
{
  if(getAnimationID() > 0)  //有动画,进一步设置
  {
      setIsWithAnimation(true);
     
      do {
          
          SqliteResolver* animateResolver = SqliteResolver::create(TABLE_ANIMATIONS, getAnimationID());
          CC_BREAK_IF(!animateResolver);
          
          char* animationName = animateResolver->loadSimpleSprite();
          CC_BREAK_IF(!animationName);
          
          ContactAnimateSprite* contactAnimateSprite = ContactAnimateSprite::create(animationName);
          contactAnimateSprite->setIdleAnimation(getIdleAnimation());
          contactAnimateSprite->setDisappearAnimationAnimation(getDisappearAnimationAnimation());
          contactAnimateSprite->setDisappearMusicID(getDisappearMusicID());
          contactAnimateSprite->onStarted();
          setContactAnimateSprite(contactAnimateSprite);
          
          MusicPlayer* musiPlayer = MusicPlayer::getInstance();//加载音乐
          CC_BREAK_IF(!musiPlayer);
          musiPlayer->preloadEffect(getDisappearMusicID());
          musiPlayer->preloadEffect(getIdleMusicID());
          musiPlayer->preloadEffect(getOnCollisionMusicID());

          
      } while (0);
      
      
  }

}

void HitBox::onCollsion(AnimationSprite* pTarget)
{
    
  if((getCollisionAnimationID() > 0) && (getCollisionAnimation() != ""))
     {
         do {
             
             SqliteResolver* animateResolver = SqliteResolver::create(TABLE_ANIMATIONS, getCollisionAnimationID());
             CC_BREAK_IF(!animateResolver);
             
             char* animationName = animateResolver->loadSimpleSprite();
             CC_BREAK_IF(!animationName);
                         
             ContactAnimateSprite* collisonAnimateSprite = ContactAnimateSprite::create(animationName);
             if(collisonAnimateSprite != NULL)
             {
                 collisonAnimateSprite->playAnimation(getCollisionAnimation().c_str());
                 collisonAnimateSprite->setDisappearMusicID(getDisappearMusicID());
                
                 Point3D worlPos = BodyRegion::getAnimateRegionPos(pTarget, getCollisionAnimationRegion());//播放的世界坐标
                 Point3D relativePos = worlPos - pTarget->getCenterPosition3D();//相对坐标
                 collisonAnimateSprite->setPosition(relativePos.x, relativePos.y + relativePos.z);
                 
                 pTarget->addChild(collisonAnimateSprite);//在受伤者身上播放动画
                 MusicPlayer* musiPlayer = MusicPlayer::getInstance();
                 if(musiPlayer != NULL)
                 {
                     musiPlayer->playEffect(getOnCollisionMusicID());
                 }
             }
             
         } while (0);
         
     }
    
}







