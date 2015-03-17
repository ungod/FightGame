#include "RoleFilter.h"




RoleFilter::RoleFilter()
{
    
}


RoleFilter::~RoleFilter()
{
   
}





SkillFilter RoleFilter::getFilter(EnumRoleFilter filter)
{
    SkillFilter ret;
    
    if(filter == eRoleFilterPlayer)
    {
        ret.attackBits = PLAYER_ATTACK_BOX_CATEGORY;
        ret.categoryBits = PLAYER_CATEGORY;
        ret.maskBits = PLAYER_MASK_BITS;
    }
    
    else if(filter == eRoleFilterMonster)
    {
        ret.attackBits = MONSTER_ATTACK_BOX_CATEGORY;
        ret.categoryBits = MONSTER_CATEGORY;
        ret.maskBits = MONSTER_MASK_BITS;
    }
        
    
    return ret;

}


SkillFilter RoleFilter::getOpponentFilter(EnumRoleFilter filter)//获取对手的filter
{
    SkillFilter ret;
    
    if(filter == eRoleFilterPlayer)
    {
        
        ret = getFilter(eRoleFilterMonster);
    }
    
    else if(filter == eRoleFilterMonster)
    {
        ret = getFilter(eRoleFilterPlayer);
    }
    
    
    return ret;

}

EnumRoleFilter RoleFilter::getOpponentEnum(EnumRoleFilter filter)
{
    EnumRoleFilter ret;
    
    if(filter == eRoleFilterPlayer)
    {
        ret = eRoleFilterMonster;
        
    }
    
    else if(filter == eRoleFilterMonster)
    {
        ret = eRoleFilterPlayer;
    }

    
    return ret;

}














