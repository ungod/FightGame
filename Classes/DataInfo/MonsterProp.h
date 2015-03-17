#pragma once

#include "cocos2d.h"
#include "string"
#include "RoleProperty.h"

USING_NS_CC;
using namespace std;

enum MonsterType
{
	NORMAL_MONSTER = 0,
	ELITE_MONSTER,
	BOSS_MONSTER
};

/************************************************************************
* 怪物属性
************************************************************************/

class MonsterProp : public RoleProperty
{
public:
	MonsterProp();
	~MonsterProp();

	virtual void parse();
	virtual void resetWithOrigin();

	static MonsterProp* createWithResolver(SqliteResolver* sqlRsl);

	CC_SYNTHESIZE_READONLY(int, m_aiModuleID, AiModule);

	//@brief 经验奖励
	PROPERTY_WITH_ORIGIN(int, m_expAwarded, ExpAwarded);

	//@brief 怪物名字
	PROPERTY_WITH_ORIGIN(string, m_monsterName, MonsterName);

	//@brief 类型，0是普通怪，1是精英，2是Boss
	PROPERTY_WITH_ORIGIN(int, m_type, Type);

	//@brief 阵型
	PROPERTY_WITH_ORIGIN(int, m_group, Group);

	//@brief 脚本名字
	PROPERTY_WITH_ORIGIN(string, m_scriptName, ScriptName);

	//@brief 对话内容
	PROPERTY_WITH_ORIGIN(string, m_dialogData, DialogData);

	//@brief 对话头像
	PROPERTY_WITH_ORIGIN(int, m_headFigure, HeadFigure);
};
