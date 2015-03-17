#include "BodyRegion.h"
#include "Sprites/AnimationSprite.h"


BodyRegion::BodyRegion(Point3D centerPoint, Size size, float direction)
{
    m_bodyRegionize = size;
    m_center = centerPoint;
    m_direction = direction;

}

void BodyRegion::setCenter(Point3D centerPoint)
{
  m_center = centerPoint;
}


Point3D BodyRegion::getPosition(Region region)
{
    Point3D ret = m_center;

    switch (region)
    {
        case LeftTop: ret = leftTop(); break;
        case Top: ret = top(); break;
        case RightTop: ret = rightTop(); break;
        
        case Left: ret = left(); break;
        case Center: ret = center(); break;
        case Right: ret = right(); break;
            
        case LeftBottom: ret = leftBottom(); break;
        case Bottom: ret = bottom(); break;
        case RightBottom: ret = rightBottom(); break;
            
        default:
            break;
    }

    return  ret;
}





Point3D BodyRegion::left()
{
    
    return Point3D(m_center.x-m_bodyRegionize.width/2  * m_direction,
                   m_center.y,
                   m_center.z);
}


Point3D BodyRegion::right()
{
    
    return Point3D(m_center.x+m_bodyRegionize.width/2  * m_direction, m_center.y, m_center.z);
}

Point3D BodyRegion::top()
{
    
    return Point3D(m_center.x, m_center.y+m_bodyRegionize.height/2, m_center.z);
}

Point3D BodyRegion::bottom()
{
    
    return Point3D(m_center.x, m_center.y-m_bodyRegionize.height/2, m_center.z);
}

Point3D BodyRegion::center()
{
    
    return m_center;
}

Point3D BodyRegion::leftTop()
{
    
    return Point3D(m_center.x-m_bodyRegionize.width/2 * m_direction, m_center.y+m_bodyRegionize.height/2, m_center.z);
}

Point3D BodyRegion::rightTop()
{
    
    return Point3D(m_center.x+m_bodyRegionize.width/2 * m_direction, m_center.y+m_bodyRegionize.height/2, m_center.z);
}

Point3D BodyRegion::leftBottom()
{
    
    return Point3D(m_center.x-m_bodyRegionize.width/2 * m_direction, m_center.y-m_bodyRegionize.height/2, m_center.z);
}

Point3D BodyRegion::rightBottom()
{
    
    return Point3D(m_center.x+m_bodyRegionize.width/2 * m_direction, m_center.y-m_bodyRegionize.height/2, m_center.z);
}


Point3D BodyRegion::getAnimateRegionPos(AnimationSprite *pSprite, Region region)
{
    Point3D pos = pSprite->getCenterPosition3D();
    
    Size size(pSprite->getCenterToSides() * 2, pSprite->getCenterToBottom() * 2);
    
    int faceDirection = pSprite->getFaceDirection().x;
   // log("faceDirection:%d",faceDirection);
    BodyRegion newRegion(pos,size,faceDirection);    //初始化
    Point3D ret = newRegion.getPosition(region);//相对的位置

    return  ret;
}
