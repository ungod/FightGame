#pragma once
#include "cocos2d.h"
USING_NS_CC;


class SkillJumpBy : public ActionInterval
{
public:
    /** creates the action */
    static SkillJumpBy* create(float duration, const Point& position, float height, int jumps);
    
    /** initializes the action */
    bool initWithDuration(float duration, const Point& position, float height, int jumps);
    
    //
    // Overrides
    //
    virtual SkillJumpBy* clone() const override;
	virtual SkillJumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
protected:
    Point           m_startPosition;
    Point           m_delta;
    float           m_height;
    int             m_jumps;
    Point           m_previousPos;
    float           m_faceDirection;//角色的脸朝向
    
};
