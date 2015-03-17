#include "HudLayer.h"
#include "DataManager.h"

using namespace cocos2d;

HudLayer::HudLayer(void)
{
	m_dPad = NULL;
    m_skillHudLayer = NULL;
	m_sBar = NULL;
	m_bossBar = NULL;
	m_goTips = NULL;
}

HudLayer::~HudLayer(void)
{
    CC_SAFE_RELEASE(m_dPad);
    CC_SAFE_RELEASE(m_skillHudLayer);
}

bool HudLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
        DataManager::getInstance()->setHudLayer(this);

		m_dPad = DirectionPad::create(CCString::create(STEEL_WHEEL_IMG), 64);
        m_dPad->retain();
		m_dPad->setPosition(Point(100, 110));
		m_dPad->setOpacity(200);
		this->addChild(m_dPad);

        m_skillHudLayer = SkillHudLayer::create();
        m_skillHudLayer->retain();
        this->addChild(m_skillHudLayer);

		Size s = Director::getInstance()->getWinSize();

		m_goTips = Sprite::createWithTexture(TextureCache::getInstance()->textureForKey(GO_TIPS));
		m_goTips->setVisible(false);
		m_goTips->setPosition(Point(s.width - m_goTips->getContentSize().width/2, s.height/2));
		this->addChild(m_goTips);

		LabelTTF* l1 = LabelTTF::create("World", "Times New Roman", 30);
		LabelTTF* l2 = LabelTTF::create("Hello", "Times New Roman", 18);

		l1->setColor(ccColor3B(255, 0, 0));
		l2->setColor(ccColor3B(0, 255, 0));
		l1->setPosition(Point(l1->getContentSize().width + 50, 50));
		l2->setPosition(Point(50, 50));

		RenderTexture* t = RenderTexture::create(256, 256);
		//t->beginWithClear(1.0f, 1.0f, 1.0f, 1.0f);
		t->begin();
		l1->visit();
		l2->visit();
		t->end();

		Sprite* sp = Sprite::createWithTexture(t->getSprite()->getTexture());
		addChild(sp);

		sp->getTexture()->setAntiAliasTexParameters();
		sp->setPosition(Point(350, 200));
		sp->setFlipY(1);
        
		bRet = true;
	} while (0);

	return bRet;
}

void HudLayer::createHeroBar()
{
	m_sBar = StatusBar::create(DataManager::getInstance()->getGameLayer()->getHero());
	m_sBar->retain();
	m_sBar->setPosition(Point(198, 400));
	m_sBar->setCascadeOpacityEnabled(true);
	m_sBar->setOpacity(200);
	this->addChild(m_sBar);
}

void HudLayer::createBossBar()
{
	m_bossBar = StatusBar::create(DataManager::getInstance()->getGameLayer()->getBoss());
	m_bossBar->retain();
	m_bossBar->setPosition(Point(548, 400));
	m_bossBar->setCascadeOpacityEnabled(true);
	m_bossBar->setOpacity(200);
	this->addChild(m_bossBar);
}

void HudLayer::setPortalTipsVisible(bool visible)
{
	if (m_goTips == NULL) return;

	m_goTips->setVisible(visible);
}