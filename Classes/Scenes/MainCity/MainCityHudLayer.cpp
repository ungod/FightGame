#include "MainCityHudLayer.h"
#include "Includes/Resources.h"

using namespace cocos2d;

MainCityHudLayer::MainCityHudLayer(void)
{
	m_dPad = NULL;
   
}

MainCityHudLayer::~MainCityHudLayer(void)
{
    CC_SAFE_RELEASE(m_dPad);
    
}

bool MainCityHudLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
       

		m_dPad = DirectionPad::create(CCString::create(STEEL_WHEEL_IMG), 64);
        m_dPad->retain();
		m_dPad->setPosition(Point(100, 110));
		m_dPad->setOpacity(200);
		this->addChild(m_dPad);

        
		bRet = true;
	} while (0);

	return bRet;
}

