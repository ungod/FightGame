#pragma once
#include "Defines.h"
#include "cocos2d.h"
#include "Geometries/BodyRegion.h"
USING_NS_CC;
using namespace std;

/*角色动作等各种参数
 
 
 
 */


class AnimateData
{
public:
    AnimateData();
    

    //角色的设定速度
	CC_SYNTHESIZE(Point, m_velocity, Velocity);
    
	//measurements
	CC_SYNTHESIZE(float, m_centerToSides, CenterToSides);//角色中心点到左右的距离
	CC_SYNTHESIZE(float, m_centerToBottom, CenterToBottom);//角色中心点到上下边界的距离

	CC_SYNTHESIZE(BoundingBox, m_hitBox, Hitbox);//角色受伤害框

};




