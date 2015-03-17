#pragma once
#include "cocos2d.h"
#include "VisibleRect.h"


#include "Includes/Resources.h"
#include "Includes/SkillNames.h"
USING_NS_CC;


#ifndef CC_ENABLE_CHIPMUNK_INTEGRATION
#define CC_ENABLE_CHIPMUNK_INTEGRATION 0
#endif

#ifndef CC_ENABLE_BOX2D_INTEGRATION
#define CC_ENABLE_BOX2D_INTEGRATION 1
#endif


// 1 - convenience measurements
#define SCREEN CCDirector::getInstance()->getVisibleSize()
#define CENTER Point(VisibleRect::center().x, VisibleRect::center().y)
//#define CURTIME GetCurTime()

#define INT_SIGN(v) (v < 0 ? -1 : 1)

#define PLAYER_TAG    0x0f  //角色的tag
#define MONSTER_TAG   0xf0
#define CONTACT_TAG	  0x0f00
#define SKILL_TAG     0x1f00 //技能也属于碰撞体

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif


#define GROUND_CATEGORY              0x0001   //地面
#define MONSTER_CATEGORY             0X0002   //对手伤害框
#define PLAYER_CATEGORY              0X0004   //玩家伤害框
#define MONSTER_ATTACK_BOX_CATEGORY  0x0008   //对手攻击框
#define PLAYER_ATTACK_BOX_CATEGORY   0x0010   //玩家攻击框
#define ITEM_CATEGORY				 0x0020   //场景互动物品

#define GROUND_MASK_BITS   (PLAYER_CATEGORY | PLAYER_ATTACK_BOX_CATEGORY | MONSTER_CATEGORY | MONSTER_ATTACK_BOX_CATEGORY)    //地面碰撞检测
#define PLAYER_MASK_BITS   (MONSTER_ATTACK_BOX_CATEGORY | ITEM_CATEGORY)
#define MONSTER_MASK_BITS  (PLAYER_ATTACK_BOX_CATEGORY)
#define ITEM_MASK_BITS	   (PLAYER_CATEGORY)

#define Z_ATTACK_RANGE  20   //z轴上有效的攻击范围
#define SCALE_FACTOR    1.6f   //角色的缩放因子

#define INFINITE_POINT Point(FLT_MAX, FLT_MAX)

//角色在box2d下的filter
typedef enum{eRoleFilterPlayer = 0, eRoleFilterMonster, eRoleFilterBuff, eRoleFilterEnd}EnumRoleFilter;


// 3 - enumerations
typedef enum _ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockedOut,
    kActionStateRunSkill
    
} ActionState;



// 4 - structures
typedef struct _BoundingBox
{
	cocos2d::Rect actual;
	cocos2d::Rect original;
} BoundingBox;


inline double GetCurTime()
{
	timeval tv;
	gettimeofday(&tv, NULL);
    double ret = (double)tv.tv_sec  + (double)tv.tv_usec / 1000000;  //毫秒
	return ret;
};



