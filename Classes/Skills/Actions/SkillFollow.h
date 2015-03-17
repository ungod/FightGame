#pragma once
#include "cocos2d.h"
#include "Geometries/Point3D.h"
#include "Sprites/AnimateBase/Animate3D.h"
USING_NS_CC;


//对目标的某个点进行跟随的动作类

class SkillFollow : public Action
{
public:
   
    //@brief 相对于角色的中心点的位置
    static SkillFollow* create(Node *pSkillFollowedNode, const Point3D& relativePosition = Point3D(0,0,0));
    
    SkillFollow()
    : m_skillFollowedNode(NULL)
    , m_relativePosition(Point3D(0,0,0))
    {}
    virtual ~SkillFollow(void);
    

    bool initWithTarget(Node *pSkillFollowedNode, const Point3D& relativePosition = Point3D(0,0,0));
    
    //
    // Override
    //
	virtual SkillFollow* clone() const override;
	virtual SkillFollow* reverse() const override;
    virtual void step(float dt) override;
    virtual bool isDone(void) const override;
    virtual void stop(void) override;
    
protected:
    // node to SkillFollow
    Node *m_skillFollowedNode;
	Point3D  m_relativePosition;
    
};
