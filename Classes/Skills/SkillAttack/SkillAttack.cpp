#include "SkillAttack.h"
#include "../SkillSystem/SkillSystem.h"


SkillAttack::SkillAttack()
{
    m_attackRate = 0;
    m_skill = NULL;
}

SkillAttack::~SkillAttack()
{
    CC_SAFE_RELEASE(m_skill);

}



SkillAttack* SkillAttack::create(SkillProperty* skillProperty)
{
    SkillAttack* pRet = new SkillAttack();
    if(pRet && pRet->initWithSkillProperty(skillProperty))
    {
        pRet->autorelease();
        return pRet;
    
    }
    
    CC_SAFE_RELEASE(pRet);
    pRet = NULL;
    return NULL;
    
}

bool SkillAttack::initWithSkillProperty(SkillProperty* skillProperty)
{
    bool bRet = false;
    
    do {
                
        CC_BREAK_IF(!skillProperty);
        
        Skill* skill = SkillSystem::create(skillProperty->getSkillID());
        CC_BREAK_IF(!skill);
        
        setSkill(skill);

        
        bRet = true;
    } while (0);
    
    
    
    return bRet;
}









