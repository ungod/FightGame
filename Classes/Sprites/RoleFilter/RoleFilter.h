#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <Box2D/Box2D.h>
#include "Defines.h"
USING_NS_CC_EXT;
USING_NS_CC;



struct SkillFilter
{
    SkillFilter()
    {
        categoryBits = (uint16)PLAYER_CATEGORY;
        attackBits = (uint16)PLAYER_ATTACK_BOX_CATEGORY;
        maskBits = (uint16)PLAYER_MASK_BITS;
        
    }
    
    uint16 categoryBits;//伤害框的
    uint16 maskBits;
    uint16 attackBits;  //攻击框的
};

class RoleFilter 
{
public:
	RoleFilter();
	~RoleFilter();
    
    static SkillFilter getOpponentFilter(EnumRoleFilter filter);//获取对手的filter
    static EnumRoleFilter getOpponentEnum(EnumRoleFilter filter);//获取对手的filer的枚举
    static SkillFilter  getFilter(EnumRoleFilter filter);//通过类型获取filter

};
