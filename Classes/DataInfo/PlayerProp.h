#pragma once

#include "cocos2d.h"
#include "RoleProperty.h"

USING_NS_CC;
using namespace std;

/************************************************************************/
/* 玩家属性
************************************************************************/

class PlayerProp : public RoleProperty
{
public:
	PlayerProp();
	~PlayerProp();

	static PlayerProp* createWithResolver(SqliteResolver* dict);

	virtual void parse();
	virtual void resetWithOrigin();

	//@brief 升级所需经验
	PROPERTY_WITH_ORIGIN(int, m_experience, Experience);
    
    //@brief 拥有的技能列表ID,指向attacks表
    CC_SYNTHESIZE(int, m_attackListID, AttackListID);
};
