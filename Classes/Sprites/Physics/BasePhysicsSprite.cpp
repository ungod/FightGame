#include "BasePhysicsSprite.h"
#include "Box2D/Box2D.h"
#include "Defines.h"

BasePhysicsSprite::BasePhysicsSprite()
:m_body(NULL)
, m_PTMRatio(PTM_RATIO)
{}



b2Body* BasePhysicsSprite::getBody() const
{
    return m_body;
}

void BasePhysicsSprite::setBody(b2Body *pBody)
{
    m_body = pBody;
}

float BasePhysicsSprite::getPTMRatio() const
{
    return m_PTMRatio;
}

void BasePhysicsSprite::setPTMRatio(float fRatio)
{
    m_PTMRatio = fRatio;
}


void BasePhysicsSprite::setPosition(const Point &pos)
{
           
    
    Node::setPosition(pos);
    if(m_body != NULL)
    {
        float angle = m_body->GetAngle();
        m_body->SetTransform(b2Vec2(pos.x / m_PTMRatio, pos.y / m_PTMRatio), angle);
    }
    

}



void BasePhysicsSprite::setRotation(float fRotation)
{
    if(m_body != NULL)
    {
        b2Vec2 p = m_body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        m_body->SetTransform(p, radians);

    }
    
    Node::setRotation(fRotation);
           
    
}

