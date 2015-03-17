#include "ContactHandler.h"
#include "Skills/skill.h"
#include "Sprites/AnimationSprite.h"
#include "Sprites/Entity/SkillContactSprite.h"

ContactHandler::ContactHandler()
{


}

ContactHandler::~ContactHandler()
{

}

void ContactHandler::addSkillMap(SkillContactSprite* skillSprite, Skill* skill)
{
    m_skillMap.insert(SkillMap::value_type(skillSprite,skill));
}


void ContactHandler::addSkillList(SkillContactSprite* skillSprite, AnimationSprite* targetSprite)
{
    SpriteCollideSheet sheet;
    sheet.contactSprite = skillSprite;
    sheet.targetSprite = targetSprite;
    
    m_skillList.push_back(sheet);

}



void ContactHandler::handle()
{
    onHandleContact();

    onHandlerPlayer();//注意::必须先处理攻击对象,然后再处理技能
    
    onHandleSkill();//处理技能
}



void ContactHandler::onHandlerPlayer()
{
    ContactList::iterator listIter ;
    for(listIter = m_skillList.begin() ; listIter != m_skillList.end(); listIter++)
    {
        SpriteCollideSheet& player = *listIter;
        SkillContactSprite* skillSprite = (SkillContactSprite*)player.contactSprite;
        AnimationSprite* target = player.targetSprite;
        
        if( target->getActionState() != kActionStateKnockedOut  && target->getBody() != NULL)//查询受到伤害
        {
            Skill* skill = skillSprite->getSkillParent();//获取技能实例
            skill->onCollsion(skillSprite, target);
           
        }
    }
    m_skillList.clear();
    


}



void ContactHandler::onHandleSkill()
{
    SkillMap::iterator mapIter;//删除技能部件
    for (mapIter = m_skillMap.begin(); mapIter != m_skillMap.end(); )
    {
        SkillContactSprite* sprite = mapIter->first;
        if(sprite->getHitMaxNum() <= 0 )
        {
            mapIter->second->removeSkill(mapIter->first);//从技能列表中删除
        }
        
        m_skillMap.erase(mapIter++);
    }
    
    m_skillMap.clear();

}

void ContactHandler::addContactList( ContactSprite* contact, AnimationSprite* target )
{
	SpriteCollideSheet sheet;
	sheet.contactSprite = contact;
	sheet.targetSprite = target;

	m_contactList.push_back(sheet);
}

void ContactHandler::onHandleContact()
{
	ContactList::iterator listIter;

	for (listIter = m_contactList.begin(); listIter != m_contactList.end(); listIter++)
	{
		ContactSprite* c = listIter->contactSprite;
		AnimationSprite* a = listIter->targetSprite;

		c->onCollsion(a);
	}
}
