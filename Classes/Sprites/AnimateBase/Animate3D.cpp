#include "Animate3D.h"
#include "Sqlite/SqliteResolver.h"
#include "Skills/Actions/SkillMoveBy.h"

Animate3D::Animate3D()
{
    m_x = m_y = m_z = 0;

}


void Animate3D::setPosition3D(Point3D position)
{
    setX(position.x);
    setY(position.y);
    setZ(position.z);

}


Point3D Animate3D::getPosition3D()
{
    return Point3D(m_x, m_y, m_z);
}


Point3D Animate3D::getCenterPosition3D()
{
    return getPosition3D();
}


void Animate3D::runActionWithLanding(Sequence* action)
{
    Node* node = dynamic_cast<Node*>(this);
    if(node == NULL)
    {
        onFallGround();
        return;
    }

    
    
    node->stopAllActions();
    Sequence* sequance;
    
    if(action != NULL)//有运动轨迹的
    {
        sequance = SqliteResolver::SequenceWithCallback(action,
                                                       CallFunc::create(CC_CALLBACK_0( Animate3D::langding,this )));
    }
    
    else
    {
        sequance = Sequence::create(CallFunc::create(CC_CALLBACK_0( Animate3D::langding,this )), NULL);
    }
    
    node->runAction(sequance);
    
}



void Animate3D::langding()
{
    Node* node = dynamic_cast<Node*>(this);
    if(node == NULL)
    {
       onFallGround();
        return;
    }
        
    if(getY() > 0 )//处于地平面之上
    {
        node->stopAllActions();
        float y = getY();
        float time = y / 400;//除以下落速度得到时间
        
        Sequence* sequance = Sequence::create(SkillMoveBy::create(time, Point3D(0, -y,0)),
                                              CallFunc::create(CC_CALLBACK_0( Animate3D::onFallGround,this ))
                                              ,NULL);
        node->runAction(sequance);
        
    }
    
    else
    {
        onFallGround();
    }


}



void Animate3D::onFallGround()
{

}



