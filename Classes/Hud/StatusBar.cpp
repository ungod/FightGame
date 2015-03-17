#include "StatusBar.h"
#include "Includes/Resources.h"
#include "DataManager.h"

StatusBar::StatusBar()
{
	m_pHead = NULL;
	m_pBloodBar = NULL;
	m_pManaBar = NULL;
}

StatusBar::~StatusBar()
{

}

StatusBar* StatusBar::create(AnimationSprite* owner)
{
	StatusBar *pRet = new StatusBar();
	if (pRet && pRet->init(owner))
	{
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool StatusBar::init(AnimationSprite* owner)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName(STATUS_BG));

		m_pOwner = owner;
		m_pHead = Sprite::createWithSpriteFrameName(HEAD_PNG);
		m_pHead->retain();
		addChild(m_pHead);
		m_pHead->setPosition(Point(59, 81));

		m_pBloodBar = ProgressTimer::create(Sprite::createWithSpriteFrameName(BLOOD_BAR));
		m_pBloodBar->retain();
		m_pBloodBar->setType(ProgressTimerType::BAR);
		m_pBloodBar->setMidpoint(Point(0, 0));
		m_pBloodBar->setBarChangeRate(Point(1, 0));
		m_pBloodBar->setPercentage(100);
		addChild(m_pBloodBar);
		m_pBloodBar->setPosition(Point(182, 78));

		m_pManaBar = ProgressTimer::create(Sprite::createWithSpriteFrameName(MANA_BAR));
		m_pManaBar->retain();
		m_pManaBar->setType(ProgressTimerType::BAR);
		m_pManaBar->setMidpoint(Point(0, 1));
		m_pManaBar->setPercentage(100);
		addChild(m_pManaBar);
		m_pManaBar->setPosition(Point(172, 61));

		m_pOwner->getRoleProperty()->addCallback(CC_CALLBACK_1(StatusBar::onCurrentHPChange, this), RoleProperty::eCurrentHP);

		m_pLevel = LabelTTF::create(String::createWithFormat("%d",m_pOwner->getRoleProperty()->getLevel())->getCString(), "Times New Roman", 12);
		addChild(m_pLevel);
		m_pLevel->setPosition(Point(36, 35));

		bRet = true;
	} while (0);

	return bRet;
}

void StatusBar::setOpacity( GLubyte opacity )
{
	m_pBloodBar->setOpacity(opacity);
	m_pManaBar->setOpacity(opacity);
}

void StatusBar::onCurrentHPChange(RoleProperty* prop)
{
	float f = ((float)prop->getCurrentHP() / prop->getMaxHP())*100;
	m_pBloodBar->setPercentage(f);

}
