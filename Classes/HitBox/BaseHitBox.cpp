#include "BaseHitBox.h"
#include "Defines.h"


BaseHitBox::BaseHitBox()
{
    m_isWithAnimation = false;
    m_delayTime = 0;
    m_duration = 0;
    m_collideRate = 0;
    m_hitMaxNum = 1;
    m_hitSingleMaxNum = 1;
    m_bodySize = Size::ZERO;
    m_aPPearRegion = BodyRegion::Center;
    m_aPPearPosition = Point3D(0,0,0);
    m_ztolerance = Z_ATTACK_RANGE;
    m_animationID = 0;
    m_idleMusicID = 0;
    m_disappearMusicID = 0;
    m_onCollisionMusicID = 0;
    
    m_collisionAnimation = "";
    m_collisionAnimationID = 0;
    m_collisionAnimationRegion = BodyRegion::Center;
    m_collisionAnimationPos = Point3D(0,0,0);
    
    m_motionCurve = NULL;
    m_onCollisionMotionCurve = NULL;
    m_onCollisionAttackerMotionCurve = NULL;
    m_onCollisionInjuredMotionCurve = NULL;
    
    m_damageConstantWithAP = NULL;
	m_damageFactorWithAP = NULL;
	m_damageConstant = NULL;
	m_damageFactor = NULL;
}

BaseHitBox::~BaseHitBox()
{
   CC_SAFE_RELEASE(m_motionCurve);
   CC_SAFE_RELEASE(m_onCollisionAttackerMotionCurve);
   CC_SAFE_RELEASE(m_onCollisionInjuredMotionCurve);
}




