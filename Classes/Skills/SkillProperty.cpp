#include "SkillProperty.h"

#include "Reader/RoleResolver.h"



SkillProperty* SkillProperty::create(int ID)
{
    SkillProperty* pRet = new SkillProperty();
    if(pRet && pRet->initWithID(ID))
    {
        pRet->autorelease();
        return pRet;
    
    }
    
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;
}


SkillProperty::SkillProperty()
{
    m_skillID = 0;
    m_MPConsume = 0;

  
}



SkillProperty::~SkillProperty()
{
   
}





bool SkillProperty::initWithID(int ID)
{
    bool bRet = false;    
    do
    {
        SqliteResolver* resolver = SqliteResolver::create(TABLE_SKILL_PROPERTY, ID);
        CC_BREAK_IF(!resolver);
        
        m_skillID = resolver->getInt("SkillID");
        m_MPConsume = resolver->getInt("MPConsume");
        
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}








