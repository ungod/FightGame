#pragma once

#include "cocos2d.h"
#include "PlayerProp.h"
#include "MonsterProp.h"

USING_NS_CC;
using namespace std;

class PropResolver : public RoleProperty
{
public:
	PropResolver();
	~PropResolver();

	PlayerProp* createPlayerProp(int id);
	MonsterProp* createMonsterProp(int id);

};
