#include "SkillContactSprite.h"
#include "Skills/Actions/SkillFollow.h"
#include "Skills/Actions/SkillMoveBy.h"
#include "../RoleFilter/RoleFilter.h"

class SkillSystem;

SkillContactSprite::SkillContactSprite()
{
    m_skillParent = NULL;
    m_delayTime = 0;
	m_bIsBullet = true;
}

SkillContactSprite* SkillContactSprite::create(int ID)
{
    SkillContactSprite* pRet = new SkillContactSprite();
    if (pRet && pRet->initWithHitBoxID(ID))
    {
        pRet->autorelease();
		pRet->setTag(CONTACT_TAG);
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

void SkillContactSprite::onStarted()
{
	EnumRoleFilter filter = getSkillParent()->getOwner()->getRoleFilter();
	m_categoryBits =  RoleFilter::getFilter(filter).attackBits;
	m_maskBits = RoleFilter::getOpponentFilter(filter).categoryBits;

    initBody();
    
    int faceDirction = getSkillParent()->getDirection().x;
    Point3D ownerPos = getSkillParent()->getOwner()->getCenterPosition3D();
    Point3D appearOwnerPos = BodyRegion::getAnimateRegionPos(getSkillParent()->getOwner(), getAppearRegion());//出现相对的位置
   //  log("ContactSprite::onStarted()%d %f %f %f",getSkillParent()->getSkillFollow(),appearOwnerPos.x, appearOwnerPos.y,appearOwnerPos.z);
    Point3D pos = appearOwnerPos + getAppearPosition()*faceDirction;
    
    setPosition3D(pos);
    //log("ContactSprite::onStarted() %f %f %f",getAppearPosition().x, getAppearPosition().y,getAppearPosition().z);
    
    if(getSkillParent()->getSkillFollow() == 0) //不跟随
    {
        if(getMotionCurve() != NULL)
         runAction(getMotionCurve());
    }
    
    else//跟随
    {
        Point3D delataPos = pos - ownerPos;
        Point3D relativePos = Point3D(delataPos.x * faceDirction, delataPos.y, delataPos.z);
        Action* action = SkillFollow::create(getSkillParent()->getOwner(), relativePos);
        runAction(action);
    }
    
    
    MusicPlayer* musiPlayer = MusicPlayer::getInstance();
    if(musiPlayer != NULL)
    {
        musiPlayer->playEffect(getIdleMusicID());
    }
    
}

void SkillContactSprite::onCollsion(AnimationSprite* pTarget)
{
    if(pTarget->getCurrentSkill() != NULL)//被攻击者处于使用技能状态
    {
        switch (pTarget->getCurrentSkill()->getSkillHitJudgement())
        {
            case Skill::HurtAndInterrupt :
				if (pTarget->hurtWithHitBox(this, getSkillParent()->getOwner()))
				{
					HitBox::onCollsion(pTarget);
					pTarget->stopSkills();
					pTarget->runSequanceAction(getOnCollisionInjuredMotionCurve() != NULL ? getOnCollisionInjuredMotionCurve()->clone(): NULL);
				}

             break;
             
            case Skill::HurtWithoudInterrupt:
				if (pTarget->hurtWithHitBox(this, getSkillParent()->getOwner()))
				{
					HitBox::onCollsion(pTarget);
				}
                            
                break;
                
            case Skill::NoHurt:
                
                break;
                
            default:
                break;
        }
        
        
    
    }
    
    else if (pTarget->hurtWithHitBox(this, getSkillParent()->getOwner()))//不使用技能状态
    {
        HitBox::onCollsion(pTarget);
        pTarget->runSequanceAction(getOnCollisionInjuredMotionCurve() != NULL ? getOnCollisionInjuredMotionCurve()->clone(): NULL);
    
    }
    
    
    if(getOnCollisionMotionCurve() != NULL && !getSkillParent()->getSkillFollow())//伤害框本身
    {
       this->stopAction(getMotionCurve());
       Sequence* motionCurve = getOnCollisionMotionCurve()->clone();
       this->runAction(motionCurve);
    }
    
    
    if(getOnCollisionAttackerMotionCurve() != NULL)//攻击者
    {
        getSkillParent()->getOwner()->stopAllActions();
        getSkillParent()->getOwner()->runSequanceAction(getOnCollisionAttackerMotionCurve()->clone());
    }


}