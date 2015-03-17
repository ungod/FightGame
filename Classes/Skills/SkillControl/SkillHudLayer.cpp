#include "SkillHudLayer.h"
#include "VisibleRect.h"
#include "cocos2d.h"
#include "Scenes/Game/GameScene.h"
#include "SKills/SkillSystem/SkillSystem.h"
#include "Sqlite/SqliteResolver.h"


USING_NS_CC;




SkillHudLayer::SkillHudLayer()
{
    m_skillMenu = NULL;
    m_attackItem = NULL;
    
    m_itemPosition = Point::ZERO;
    m_itemVisible = true;
    m_skillID = 1;
    m_skillCDTime = 0;
}


SkillHudLayer::~SkillHudLayer()
{
    CC_SAFE_RELEASE(m_skillMenu);
    CC_SAFE_RELEASE(m_attackItem);
}


void SkillHudLayer::onAttack()
{
    //注册一个监听事件到GameScene
    NotificationCenter::getInstance()->postNotification(ON_SKILL_PRESS, m_attackItem);
}


/**技能菜单点击回调******/
void SkillHudLayer::onSkill(Object* selectedItem)
{
    SkillItem* item = ( SkillItem*)selectedItem;
    
    //注册一个监听事件到GameScene
    NotificationCenter::getInstance()->postNotification(ON_SKILL_PRESS, item);
}



bool SkillHudLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

        m_attackItem = SkillItem::create("Public/attack1.png","Public/attack2.png",CC_CALLBACK_0(SkillHudLayer::onAttack, this));
        m_attackItem->setPosition(VisibleRect::rightBottom() - Point(90,-100));
        m_attackItem->retain();
        m_attackItem->setTag(e_skillBtattack);
        
        
        
        m_skillMenu = CCMenu::create(m_attackItem, NULL);
        m_skillMenu->setAnchorPoint(Point(0,0));
        m_skillMenu->setPosition(VisibleRect::leftBottom());
        m_skillMenu->retain();
        addChild(m_skillMenu);
        
        Point center = m_attackItem->getPosition();
        CC_BREAK_IF(!initItems(center));
        
        bRet = true;
        
    }while(0);
    
    
    return bRet;
}

bool  SkillHudLayer::initItems(Point center)
{
    bool bRet = true;
    
    do {

        SqliteHelper* helper = SqliteHelper::getInstance();
        CC_BREAK_IF(!helper);
        
        String* sql = String::createWithFormat("SELECT * FROM %s ORDER BY ID",TABLE_SKILL_ITEMS);
        SqliteTable* itemTable = helper->getTable(sql->getCString());
        CC_BREAK_IF(!itemTable);
        
        int count = itemTable->numOfRows();//item的个数
        for( int i = 0; i < count; i++)
        {
            itemTable->setRow(i);
            SqliteResolver* resolver = SqliteResolver::create(itemTable);
            m_skillID = resolver->getInt("SkillID");
            m_itemVisible = resolver->getInt("Visible");
            m_itemPosition = resolver->getPoint("Position");
            m_skillCDTime = resolver->getFloat("SkillCD");
            
           // log("%f %d %f %f", m_skillCDTime, m_itemVisible, m_itemPosition.x, m_itemPosition.y);
            
            
            SkillItem *skillItem = SkillItem::create("Public/skill1.png","Public/skill2.png","Public/skill2.png");
            CC_BREAK_IF(!skillItem);
            
            Skill* pSkill = SkillSystem::create(m_skillID);
            CC_BREAK_IF(!pSkill);
            skillItem->setSkill(pSkill);
            
            
            skillItem->setCallback(CC_CALLBACK_0(SkillHudLayer::onSkill, this, skillItem));
            skillItem->setPosition(center + m_itemPosition);
            skillItem->setSkillCDTime(m_skillCDTime);
            skillItem->setVisible(m_itemVisible);
            
            skillItem->setTag(e_skillBt0 + i);
            m_skillMenu->addChild(skillItem,i, e_skillBt0 + i);
            
            
        }
  
      } while (0);  
        
    return bRet;
}




SkillItem* SkillHudLayer::getSkillButton( int index)
{
    SkillItem* pRet = (SkillItem* )m_skillMenu->getChildByTag(index + e_skillBt0);
    return pRet;
}





