#include "RoleResolver.h"
#include "Defines.h"
#include "Sprites/Role/Hero.h"
#include "Sprites/Role/AiPlayer.h"
#include "DataInfo/PropResolver.h"
#include "Sprites/Role/NPCSprite.h"



RoleResolver::RoleResolver()
{
   
}

RoleResolver::~RoleResolver()
{
   
}


SimpleAnimation*  RoleResolver::getSimpleAnimation(int ID)
{
    SimpleAnimation* pRet = NULL;
    do {
        
        SqliteResolver* animateResolver = SqliteResolver::create(TABLE_ANIMATIONS, ID);
        CC_BREAK_IF(!animateResolver);
        
        char* animationName = animateResolver->loadSimpleSprite();
        CC_BREAK_IF(!animationName);
        
        pRet = SimpleAnimation::create(animationName);

    } while (0);
    
    
    return pRet;
}



Hero* RoleResolver::createHero(int id)
{
    Hero*  pRet = NULL;
    do {
		PropResolver pr;
		RoleProperty* prop = pr.createPlayerProp(id);
		CC_BREAK_IF(prop == NULL);

        SqliteResolver* resolver = SqliteResolver::create(TABLE_ROLES, prop->getRolesID());
        CC_BREAK_IF(!resolver);

        int animationID = resolver->getInt("AnimationID");
		SimpleAnimation* armatureSprite = getSimpleAnimation(animationID);
		CC_BREAK_IF(armatureSprite == NULL);

        pRet = Hero::create(armatureSprite);
        CC_BREAK_IF(!pRet);
		pRet->setRoleProperty(prop);
        
           
        roleAdvanceSet(pRet, resolver);
        
        
        int attackListID = ((PlayerProp*)prop)->getAttackListID();
        setAttackListManager(pRet, attackListID);
        
    } while (0);
    
    
    
    return pRet;


}



AiPlayer* RoleResolver::createAiPlayer(int id)
{
	AiPlayer*  pRet = NULL;
	do {
		PropResolver pr;
		RoleProperty* prop = pr.createMonsterProp(id);
		CC_BREAK_IF(prop == NULL);

        SqliteResolver* resolver = SqliteResolver::create(TABLE_ROLES, prop->getRolesID());
        CC_BREAK_IF(!resolver);
        
        int animationID = resolver->getInt("AnimationID");
		SimpleAnimation* armatureSprite = getSimpleAnimation(animationID);
		CC_BREAK_IF(armatureSprite == NULL);

		pRet = AiPlayer::create(armatureSprite);
        CC_BREAK_IF(!pRet);
		pRet->setRoleProperty(prop);
		pRet->initAccessory();
		pRet->startAiModule();
  
        roleAdvanceSet(pRet, resolver);

	} while (0);

	return pRet;
}

bool RoleResolver::roleAdvanceSet(AnimationSprite* sprite, SqliteResolver* resolver)
{
    bool bRet = false;
    do {
         setShadow(sprite, resolver);//设置影子
        
        int attackID = sprite->getRoleProperty()->getSkillListID();
        setSkillListManager(sprite, attackID);//设置普通攻击或者AI技能
        
        bRet = true;
    } while (0);
    
    return bRet;
}





void RoleResolver::setSkillListManager(AnimationSprite* sprite, int ID)
{
    do {
        CC_BREAK_IF(ID <= 0);
        
        SkillAttackManager* skillAttackManager = SkillAttackManager::create(ID);
        CCAssert(skillAttackManager != NULL, "Attack.plist error");
        CC_BREAK_IF(skillAttackManager == NULL);
        
        sprite->setSkillListManager(skillAttackManager);
    } while (0);
}


void RoleResolver::setAttackListManager(Hero* hero, int ID)
{
    do {
        CC_BREAK_IF(ID <= 0);
        
        SkillAttackManager* skillAttackManager = SkillAttackManager::create(ID);
        CCAssert(skillAttackManager != NULL, "Attack.plist error");
        CC_BREAK_IF(skillAttackManager == NULL);
        
        hero->setAttackListManager(skillAttackManager);
    } while (0);

}


void RoleResolver::setShadow(AnimationSprite* sprite, SqliteResolver* resolver)//设置影子
{
    string shadowFile = resolver->getString("ShadowFile");
    
    ShadowSprite* shadowSprite = ShadowSprite::create(shadowFile.c_str());
    if(shadowSprite == NULL)
        return;
    
    Size size = resolver->getSize("ShadowSize");
    Size contentSize = shadowSprite->getContentSize();
    shadowSprite->setExpectSize(size);
    float scaleX = size.width / contentSize.width / SCALE_FACTOR;
    float scaleY = size.height / contentSize.height / SCALE_FACTOR;
    shadowSprite->setScaleX(scaleX);
    shadowSprite->setScaleY(scaleY);

    Point pos = resolver->getPoint("ShadowPosition") / SCALE_FACTOR;
    shadowSprite->setRelativePos(pos);
    sprite->setShadow(shadowSprite);
    sprite->addChild(shadowSprite);

	Size bodySize = resolver->getSize("BodySize");
	sprite->setCenterToBottom((bodySize.height)/ 2);
	sprite->setCenterToSides((bodySize.width)/ 2);

    shadowSprite->setPosition( Point(shadowSprite->getRelativePos().x,
                                     -(bodySize.height / 2) + shadowSprite->getRelativePos().y) / SCALE_FACTOR);
    
    
    shadowSprite->setOpacity(210);
}





