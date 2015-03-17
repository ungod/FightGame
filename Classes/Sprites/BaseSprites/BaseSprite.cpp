#include "BaseSprite.h"
#include "Sprites/Physics/ContactSprite.h"


BaseSprite::BaseSprite()
{
    m_active = true;
    m_collisionNum = 0;
    m_contactSprite = NULL;
}

BaseSprite::~BaseSprite()
{

}




bool BaseSprite::canCollide(ContactSprite* contactSprite)
{
    bool bRet = false;
    
    if(contactSprite != m_contactSprite)  //没有发生碰撞过的
    {
        m_collisionNum = 0;
        m_contactSprite = contactSprite;
        bRet = true;
    }
    
    else
    {
        m_collisionNum++;
        if(m_collisionNum >= m_contactSprite->getHitSingleMaxNum())
        {
          return false;
        
        }
        
        bRet = true;
    }
    
    
    
    return bRet;

}

void BaseSprite::onSkillAnimationFinished()
{


}


void BaseSprite::onAttackAnimationFinished()
{


}

void BaseSprite::onRemoved()
{
    //log("BaseSprite::onRemoved()");

}


void BaseSprite::runSkill(Skill* pSkill)
{
    
}












