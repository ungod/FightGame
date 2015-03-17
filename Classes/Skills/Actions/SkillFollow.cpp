#include "SkillFollow.h"

//
// SkillFollow
//


SkillFollow::~SkillFollow()
{
    CC_SAFE_RELEASE(m_skillFollowedNode);
}

SkillFollow* SkillFollow::create(Node *pSkillFollowedNode, const Point3D& relativePosition)
{
    SkillFollow *pRet = new SkillFollow();
    if (pRet && pRet->initWithTarget(pSkillFollowedNode, relativePosition))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

SkillFollow* SkillFollow::clone() const
{
	// no copy constructor
	auto a = new SkillFollow();
	a->initWithTarget(m_skillFollowedNode, m_relativePosition);
	a->autorelease();
	return a;
}

SkillFollow* SkillFollow::reverse() const
{
    return clone();
}

bool SkillFollow::initWithTarget(Node *pSkillFollowedNode, const Point3D& relativePosition)
{
    CCASSERT(pSkillFollowedNode != NULL, "");
    
    pSkillFollowedNode->retain();
    m_skillFollowedNode = pSkillFollowedNode;
	m_relativePosition = relativePosition;
   
    
    return true;
}

void SkillFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    Animate3D* target = dynamic_cast<Animate3D*>(_target);//自身
    Animate3D* followedTartet = dynamic_cast<Animate3D*>(m_skillFollowedNode);//跟踪目标
    if(target == NULL || followedTartet == NULL)
        return;
    
    float direction = m_skillFollowedNode->getScaleX() / fabs(m_skillFollowedNode->getScaleX());
    Point3D directionPoint (m_relativePosition.x * direction,m_relativePosition.y, m_relativePosition.z);
    _target->setScaleX(direction);
    target->setPosition3D(followedTartet->getCenterPosition3D() + directionPoint);
    
}

bool SkillFollow::isDone() const
{
    return ( !m_skillFollowedNode->isRunning() );
}

void SkillFollow::stop()
{
    _target = NULL;
    Action::stop();
}




