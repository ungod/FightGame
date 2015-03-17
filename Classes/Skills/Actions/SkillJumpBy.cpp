#include "SkillJumpBy.h"
#include "Geometries/Point3d.h"
#include "Sprites/AnimateBase/Animate3D.h"
//
// SkillJumpBy
//

SkillJumpBy* SkillJumpBy::create(float duration, const Point& position, float height, int jumps)
{
    SkillJumpBy *pSkillJumpBy = new SkillJumpBy();
    pSkillJumpBy->initWithDuration(duration, position, height, jumps);
    pSkillJumpBy->autorelease();
    
    return pSkillJumpBy;
}

bool SkillJumpBy::initWithDuration(float duration, const Point& position, float height, int jumps)
{
    CCASSERT(jumps>=0, "Number of jumps must be >= 0");
    
    if (ActionInterval::initWithDuration(duration) && jumps>=0)
    {
        m_delta = position;
        m_height = height;
        m_jumps = jumps;
        
        return true;
    }
    
    return false;
}

SkillJumpBy* SkillJumpBy::clone(void) const
{
	// no copy constructor
	auto a = new SkillJumpBy();
	a->initWithDuration(_duration, m_delta, m_height, m_jumps);
	a->autorelease();
	return a;
}

void SkillJumpBy::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    
    m_faceDirection = 1.0f;
    if(target->getScaleX() < 0)
    {
        m_faceDirection = -1.0f;
        m_delta = Point(m_delta.x * -1,m_delta.y);
    }
    
    Animate3D* animateTarget = dynamic_cast<Animate3D*>(target);
    m_previousPos = m_startPosition = Point(animateTarget->getX(), animateTarget->getZ());
}

void SkillJumpBy::update(float t)
{
    Animate3D* target = dynamic_cast<Animate3D*>(_target);;
    if (target)
    {
        float frac = fmodf( t * m_jumps, 1.0f );
        float y = m_height * 4 * frac * (1 - frac);
        //y += _delta.y * t;
        
        target->setX(m_startPosition.x + m_delta.x * t);
        target->setY(y);
        target->setZ(m_startPosition.y + m_delta.y * t);
    }
}

SkillJumpBy* SkillJumpBy::reverse() const
{
    return SkillJumpBy::create(_duration, Point(-m_delta.x, -m_delta.y),
                          m_height, m_jumps);
}




