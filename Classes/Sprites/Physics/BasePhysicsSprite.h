#pragma once
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "ExtensionMacros.h"
USING_NS_CC;

class b2Body;


class BasePhysicsSprite : public Node
{
public:
    BasePhysicsSprite();
    
   /** Body accessor when using box2d */
    b2Body* getBody() const;
    void setBody(b2Body *pBody);
    
    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    
    virtual void setPosition(const Point &position) override;
    virtual void setRotation(float fRotation) override;
protected:
       // box2d specific
    b2Body  *m_body;
    float   m_PTMRatio;
    
    
};



