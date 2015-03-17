#pragma once

#include "Box2d/Box2D.h"
#include "cocos2d.h"
#include <list>
#include "cocos-ext.h"
USING_NS_CC_EXT;
using std::list;
USING_NS_CC;


class ContactSprite;
class AnimationSprite;
class SkillContactSprite;
class Skill;

//box2d中的碰撞后期处理
typedef struct
{
  AnimationSprite* targetSprite;
  ContactSprite* contactSprite;
}SpriteCollideSheet;

typedef std::map<SkillContactSprite*, Skill*> SkillMap;
typedef std::list<SpriteCollideSheet> ContactList;


class ContactHandler
{
public:
    ContactHandler();
    ~ContactHandler();
    
    void addSkillMap(SkillContactSprite* skillSprite, Skill* skill);
    void addSkillList(SkillContactSprite* skillSprite, AnimationSprite* targetSprite);

	void addContactList(ContactSprite* contact, AnimationSprite* target);

    virtual void handle();
protected:
    
	virtual void onHandleContact();
    virtual void onHandlerPlayer();
    virtual void onHandleSkill();
    
    //用来存放被碰撞的飞行技能子类
    SkillMap m_skillMap;
    
    //技能碰撞列表
    ContactList m_skillList;

	//普通碰撞列表
	ContactList m_contactList;
};
