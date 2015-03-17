#pragma once

#include "cocos2d.h"
#include "Geometries/Point3D.h"
USING_NS_CC;
using namespace std;

/*用来模拟角色3d行走的接口
 
 
 
 */
class Animate3D
{
public:
    Animate3D();
    
    CC_SYNTHESIZE(float, m_x, X);//x坐标
    CC_SYNTHESIZE(float, m_y, Y);//y坐标
    CC_SYNTHESIZE(float, m_z, Z);//z坐标
    
    virtual void setPosition3D(Point3D position);
    virtual Point3D getPosition3D();//这个一般是角色的中心点,但是AnimateSprite的是左下角的点
    
    virtual Point3D getCenterPosition3D();//获取中心点坐标
    
    virtual void runActionWithLanding(Sequence* action);
    virtual void langding();//强制降落到地上
    
    
     virtual void onFallGround();//掉落到地上
};




