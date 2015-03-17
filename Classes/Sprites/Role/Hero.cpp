#include "Hero.h"
#include "DataManager.h"
class DataManager;



Hero::Hero()
{
    m_attackListManager = NULL;
}


Hero::~Hero()
{
    CC_SAFE_RELEASE(m_attackListManager);
}



void Hero::attack()
{
    CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");
    
    if(!getActive())
        return;
    
    if (m_actionState == kActionStateIdle ||  m_actionState == kActionStateWalk)//攻击动作完成才可以继续攻击
	{
		m_animationSprite->playAnimation(SPRITE_ATTACK);
		m_actionState = kActionStateAttack;
        
        do {
            CC_BREAK_IF(m_attackListManager == NULL);
            Skill* attackSkill = m_attackListManager->getAttackSkill();
            
            CC_BREAK_IF(attackSkill == NULL);
            runSkill(attackSkill);
        } while (0);
        
        
    }
    
}




 Hero* Hero::create(SimpleAnimation* pBaseSprite)
{
    Hero* pRet = new Hero();
    if(pRet && pRet->initWithAnimateAction(pBaseSprite))
    {
       pRet->autorelease();
    
    }

    
    return pRet;
}


bool Hero:: initWithAnimateAction(SimpleAnimation* pAnimationSprite)
{
    bool bRet = false;
    
    do {
        
        CC_BREAK_IF(!AnimationSprite::initWithAnimateAction(pAnimationSprite));
        setRoleFilter(eRoleFilterPlayer);
        setTag(PLAYER_TAG);
        
        bRet = true;
    } while (0);


    return bRet;
}






