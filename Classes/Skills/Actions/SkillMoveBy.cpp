#include "SkillMoveBy.h"
#include "Geometries/Point3d.h"
#include "Sprites/AnimateBase/Animate3D.h"
//
// SkillMoveBy
//


SkillMoveBy* SkillMoveBy::create(float duration, Point3D delta)
{
    SkillMoveBy *pRet = new SkillMoveBy();
    pRet->initWithDuration(duration, delta);
    pRet->autorelease();
    
    return pRet;
}

bool SkillMoveBy::initWithDuration(float duration, Point3D delta)
{
    if (ActionInterval::initWithDuration(duration))
    {
        m_delta = delta;

        return true;
    }
    
    return false;
}

SkillMoveBy* SkillMoveBy::clone(void) const
{
	// no copy constructor
	auto a = new SkillMoveBy();
    a->initWithDuration(_duration, m_delta);
	a->autorelease();
	return a;
}

void SkillMoveBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    Animate3D* animateTarget = dynamic_cast<Animate3D*>(target);
    
    m_faceDirection = 1.0f;
    if(target->getScaleX() < 0)
    {
        m_faceDirection = -1.0f;
        m_delta = Point3D(m_delta.x * -1,m_delta.y, m_delta.z);
    }
    
    
    m_previous = m_start = animateTarget->getPosition3D();
    
    
    
    //log("start:%f %f %f",m_start.x, m_start.y,m_start.z);
    
}

SkillMoveBy* SkillMoveBy::reverse() const
{
    return SkillMoveBy::create(_duration, -m_delta);
}



void SkillMoveBy::update(float t)
{
    Animate3D* target = dynamic_cast<Animate3D*>(_target);
    if (target)
    {
        
        target->setPosition3D(m_start + m_delta *t);
        
    }
    
}




