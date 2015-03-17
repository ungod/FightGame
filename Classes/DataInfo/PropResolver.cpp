#include "PropResolver.h"
#include "cocos2d.h"
#include <stdlib.h>
#include <stdio.h>
#include "Utils/MiscUtils.h"
USING_NS_CC;

PropResolver::PropResolver()
{
    
}

PropResolver::~PropResolver()
{

}

PlayerProp* PropResolver::createPlayerProp( int id )
{
	SqliteResolver* sqlitRsl = SqliteResolver::create(TABLE_PLAYER_ROLE_PROPERTY, id);

	CCAssert(sqlitRsl != NULL, "Create role property failed cuz dictionary is null!");
	RETURN_NULL_IF(sqlitRsl == NULL);

	PlayerProp* p = PlayerProp::createWithResolver(sqlitRsl);
	return p;
}

MonsterProp* PropResolver::createMonsterProp( int id )
{
	SqliteResolver* sqlitRsl = SqliteResolver::create(TABLE_MONSTER_ROLES_PROPERTY, id);

	CCAssert(sqlitRsl != NULL, "Create role property failed cuz dictionary is null!");
	RETURN_NULL_IF(sqlitRsl == NULL);

	MonsterProp* p = MonsterProp::createWithResolver(sqlitRsl);
	return p;
}