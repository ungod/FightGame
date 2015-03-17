#pragma once
#include "cocos2d.h"
#include "Geometries/Point3D.h"
USING_NS_CC;

class AnimationSprite;
class Point3D;

class SkillMoveBy : public ActionInterval
{
public:

    /** creates the action */
    static SkillMoveBy* create(float duration, Point3D delta);
    
    /** initializes the action */
    bool initWithDuration(float duration, Point3D delta);
    
    //
    // Overrides
    //
    virtual SkillMoveBy* clone() const override;
	virtual SkillMoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target);
    virtual void update(float time) override;
    
protected:
    Point3D m_delta;
    Point3D m_start;
    Point3D m_previous;
    
    float   m_faceDirection;//角色的脸朝向
    
};
