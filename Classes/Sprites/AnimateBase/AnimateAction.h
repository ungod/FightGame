#pragma once

#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;
using namespace std;

class HitBox;

/**********
 *精灵角色动作的基类
 *作用:定义角色的各种动作
 *****************/


class AnimateAction
{
public:
	virtual void idle();
	virtual void attack();
	virtual void hurtWithHitBox(HitBox* hitbox, Node* attacker);
	virtual void knockout();
	virtual void walkWithDirection(Point direction);
	

    

};




