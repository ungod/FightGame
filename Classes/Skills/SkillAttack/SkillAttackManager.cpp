#include "SkillAttackManager.h"
#include "Defines.h"
#include "Skills/SkillSystem/SkillSystem.h"


SkillAttackManager::SkillAttackManager()
{
    m_skillAttackArray = NULL;
    m_nextAttackTime = 0;
    m_currentIndex = -1;
}

SkillAttackManager::~SkillAttackManager()
{
    CC_SAFE_RELEASE(m_skillAttackArray);
    
}


SkillAttackManager* SkillAttackManager::create(int ID)
{
    SkillAttackManager* pRet = new SkillAttackManager();
    if(pRet && pRet->initWithID(ID))
    {
        pRet->autorelease();
        return pRet;
    
    }
    
    CC_SAFE_RELEASE(pRet);
    pRet = NULL;
    return NULL;
    
}

bool SkillAttackManager::initWithID(int ID)
{
    bool bRet = false;
    
    do {
        
        CC_BREAK_IF(ID <= 0);
        
        
        SqliteResolver* resolver = SqliteResolver::create(TABLE_ATTACKS, ID);
        CC_BREAK_IF(!resolver);
        
        m_skillAttackArray = Array::create();
        m_skillAttackArray->retain();

        setSkillLastDelay(resolver->getFloat("SkillLastDelay"));
        //log("SkillLastDelay:%f", m_skillLastDelay);
        
        Array* skillArray = resolver->getArray("TimeAndSkillPropertyID");
        CC_BREAK_IF(skillArray == NULL);
        
        Object* obj;
        CCARRAY_FOREACH(skillArray, obj)
        {
            Point point = PointFromString( ((String*)obj)->getCString() );
            float attackRate = point.x;
            int skillPropertyID = (int)point.y;
            
           //log("SkillAttackManager::%f %d",attackRate,skillPropertyID);
            SkillProperty* pSkillProperty = SkillProperty::create(skillPropertyID);
            if(!pSkillProperty)
                continue;
            
            SkillAttack* skillAttack = SkillAttack::create(pSkillProperty);
            skillAttack->setAttackRate(attackRate);
            

            m_skillAttackArray->addObject(skillAttack);
        
        }
        
        
               
        bRet = true;
    } while (0);
    
    
    
    return bRet;
}



void SkillAttackManager::updateAttackTime()
{
    SkillAttack* attack = (SkillAttack*)m_skillAttackArray->objectAtIndex(m_currentIndex);
    float delayTime = attack->getAttackRate();
    m_nextAttackTime = GetCurTime() + delayTime;
    
}



int SkillAttackManager::getSkillIndex()
{
   if(GetCurTime() <= m_nextAttackTime)
    {
        m_currentIndex++;
       if(m_currentIndex >= getSkillCount())
        {
            m_currentIndex = 0;
        }
        
    }
    
   else//超时
   {
       m_currentIndex = 0;
       
   }
    
    
    //log("SkillAttackManager:%f %f %d",CURTIME, m_nextAttackTime,m_currentIndex);
    
    updateAttackTime();
    
    return m_currentIndex;
}


Skill* SkillAttackManager::getSkillAt(int index)
{
    CCASSERT(index >= 0 && index <getSkillCount(), "Skill index invalidate");
    if(index < 0 || index >= getSkillCount())
        return NULL;
    
    SkillAttack* attack = (SkillAttack*)m_skillAttackArray->objectAtIndex(index);
    
    Skill* pRet = attack->getSkill();
    
    return pRet;
    
}


Skill* SkillAttackManager::getSkillAtIndex(int index)
{
   
    Skill* pRet = getSkillAt(index);
    if(pRet == NULL)
        return NULL;
    
    
    return pRet->clone();
}




Skill* SkillAttackManager::getAttackSkill()
{
    
    Skill* pRet = getSkillAtIndex(getSkillIndex());
    //log("SkillAttackManager index:%d",m_currentIndex);
    return pRet;

}




int SkillAttackManager::getSkillCount()
{
    CCASSERT(m_skillAttackArray != NULL, "Skill array is NULL");
    
    int ret = m_skillAttackArray->count();
    return ret;
}









