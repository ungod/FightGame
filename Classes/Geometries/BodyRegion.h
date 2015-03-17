#pragma once
#include "Point3D.h"
#include "cocos2d.h"
USING_NS_CC;

class AnimationSprite;

class BodyRegion
{
public:
     BodyRegion(Point3D centerPoint,Size size, float direction);
    
    enum Region{LeftTop=0, Top,     RightTop,
                Left,       Center,  Right,
                LeftBottom, Bottom,  RightBottom};
    
     Point3D left();
     Point3D right();
     Point3D top();
     Point3D bottom();
     Point3D center();
     Point3D leftTop();
     Point3D rightTop();
     Point3D leftBottom();
     Point3D rightBottom();
    
    //通过region获取sprite的身体位置坐标
    static Point3D getAnimateRegionPos(AnimationSprite *pSprite, Region region);
    
    Point3D getPosition(Region region);//获取区域坐标
    
    void setCenter(Point3D centerPoint);//设置中心点坐标
    CC_SYNTHESIZE(Size, m_bodyRegionize, BodyRegionSize);
private:
    Point3D m_center;
    float m_direction;

};


