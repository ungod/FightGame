#include "SkillItem.h"
#include "Skills/SkillSystem/SkillSystem.h"


#define SKILL_ITEM_CHILD_TAG  500

SkillItem::SkillItem()
:m_strName("")
{
    m_skill = NULL;
    m_enableIcon = "";
    m_disableIcon = "";
    
    m_skillCDTime = 0;
}


SkillItem::~SkillItem()
{
  
}

SkillItem* SkillItem::create()
{
    SkillItem *pRet = new SkillItem();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}


SkillItem * SkillItem::create(const char *normalImage, const char *selectedImage)
{
    return SkillItem::create(normalImage, selectedImage, NULL, (const ccMenuCallback&)nullptr);
}


SkillItem * SkillItem::create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback)
{
    return SkillItem::create(normalImage, selectedImage, NULL, callback);
}



SkillItem * SkillItem::create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback)
{
    SkillItem *pRet = new SkillItem();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

SkillItem * SkillItem::create(const char *normalImage, const char *selectedImage, const char *disabledImage)
{
    SkillItem *pRet = new SkillItem();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, (const ccMenuCallback&)nullptr))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}


void SkillItem::onSkillStarted()
{
    this->setEnabled(false);
    
    ProgressTo *to1 = ProgressTo::create(getSkillCDTime(), 100);
    ProgressTimer *sprite = ProgressTimer::create(Sprite::create(this->getDisableIcon().c_str()));
    sprite->setType(ProgressTimer::Type::RADIAL);
    
    auto tint = Sequence::create(TintTo::create(getSkillCDTime(), 60, 255, 180),
                                 NULL);

    
    sprite->setPosition(Point(getContentSize().width / 2, getContentSize().height / 2));
    sprite->setBarChangeRate(Point(0, 1));
    addChild(sprite, 0, SKILL_ITEM_CHILD_TAG);
    sprite->runAction(Sequence::create(Spawn::create(to1, tint, NULL),CallFunc::create( CC_CALLBACK_0( SkillItem::onSkillCDFinished, this)) ,NULL) );


}

void SkillItem::onSkillFinished()
{
    
}


void SkillItem::onSkillCDFinished()
{

    setEnabled(true);
    removeChildByTag(SKILL_ITEM_CHILD_TAG);
}


void SkillItem::setEnableIcon(string icon)
{
    if(!FileUtils::getInstance()->isFileExist(icon.c_str()))
     return;
    
    m_enableIcon = icon;
    Sprite* sprite = Sprite::create(m_enableIcon.c_str());
    if(!sprite)
      return;
    
    setNormalImage(sprite);
}



void SkillItem::setDisableIcon(string icon)
{
    if(!FileUtils::getInstance()->isFileExist(icon.c_str()))
     return;
    
    m_disableIcon = icon;
    
    Sprite* spriteSelected = Sprite::create(m_disableIcon.c_str());
    if(!spriteSelected)
        return;
    
    Sprite* spriteDisabled = Sprite::create(m_disableIcon.c_str());
    if(!spriteDisabled)
        return;
    
    setSelectedImage(spriteSelected);
    setDisabledImage(spriteDisabled);

}

void SkillItem::setSkill(Skill* skill)
{
    CCAssert(skill != NULL , "skill is NULL");
    
    if (m_skill != skill && skill != NULL)
    { 
        CC_SAFE_RETAIN(skill); 
        CC_SAFE_RELEASE(m_skill); 
        m_skill = skill;
        skill->setSkillItem(this);  //绑定菜单
        
        setEnableIcon(skill->getSkillIcon());
        setDisableIcon(skill->getSkillIconDisabled());
        
        //log("itemIcon:%s %s",skill->getSkillIconDisabled().c_str(),m_disableIcon.c_str());

    }
    
    

}



bool SkillItem::setSkill(string skillFile)
{
    bool bRet = false;
    
    do {
        Skill* pSkill = SkillSystem::create(skillFile.c_str());
        
        CC_BREAK_IF(!pSkill);
        setSkill(pSkill);//设定技能

        bRet = true;
    } while (0);

    
    return bRet;
}


Skill* SkillItem::getSkill()
{
    return  m_skill->clone();
}










