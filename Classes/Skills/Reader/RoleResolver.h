#pragma once
#include "cocos2d.h"
#include "Sprites/AnimationSprite.h"
#include "Sqlite/SqliteResolver.h"

USING_NS_CC;
using namespace std;


class Hero;
class AiPlayer;
class AiObject;

class RoleResolver
{
public:
    
    RoleResolver();
    ~RoleResolver();
    
    SimpleAnimation* getSimpleAnimation(int ID);
    Hero* createHero(int id);//创建hero
	AiPlayer* createAiPlayer(int id);//创建Ai怪物
    
    
    bool roleAdvanceSet(AnimationSprite* sprite, SqliteResolver* resolver);//角色的进一步设置
    void setShadow(AnimationSprite* sprite, SqliteResolver* resolver);//设置影子
    void setSkillListManager(AnimationSprite* sprite, int ID);//设置技能管理器
    void setAttackListManager(Hero* hero, int ID);//设置普通攻击管理器

};
