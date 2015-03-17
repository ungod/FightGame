#pragma once
#include "cocos2d.h"
#include "sqlite3.h"
#include "SqliteTable.h"
#include "SqliteQuery.h"
#include "Config.h"

USING_NS_CC;
using namespace std;

#define TABLE_AI_STATES "AiStates"
#define TABLE_ANIMATIONS   "Animations"
#define TABLE_MAIN_CITY "MainCity"
#define TABLE_NPC "NPC"
#define TABLE_SKILLS       "Skills"
#define TABLE_SKILL_ITEMS        "SkillItems"
#define TABLE_HITBOXES    "HitBoxes"
#define TABLE_ATTACKS    "Attacks"
#define TABLE_PLAYER_ROLE_PROPERTY "PlayerRolesProperty"
#define TABLE_MONSTER_ROLES_PROPERTY "MonsterRolesProperty"
#define TABLE_ROLES      "Roles"
#define TABLE_MUSIC      "Music"
#define TABLE_MAPS		"Maps"
#define TABLE_SCENES    "Scenes"
#define TABLE_MONSTERS_LOADER   "MonstersLoader"
#define TABLE_SKILL_PROPERTY    "SkillProperty"


class SqliteHelper : public Object
{
public:
    static SqliteHelper* getInstance();
    SqliteHelper();
    virtual ~SqliteHelper() ;
    bool init();
    bool checkDB();
    void test();
    
    sqlite3_stmt* compile(const char *szSQL);
    int execDML(const char *szSQL);
    SqliteQuery* execQuery(const char *szSQL);
    SqliteTable* getTable(const char *szSQL);

   CC_SYNTHESIZE(sqlite3*, m_pdb, Pdb);

    
};
