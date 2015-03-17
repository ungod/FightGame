#include "MainCityScene.h"
#include "DataManager.h"
#include "EntitiesManager.h"

using namespace cocos2d;


MainCityScene* MainCityScene::create(int ID)
{ 
    MainCityScene *pRet = new MainCityScene(); 
    if (pRet && pRet->initWithID(ID))
    { 
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}



MainCityScene::MainCityScene(void)
{
	m_hudLayer = NULL;
    m_mainCityLayer = NULL;
	DataManager::getInstance()->setPhysicsEnable(false);
}

MainCityScene::~MainCityScene(void)//切换场景的时候可以用到
{
  
    
    
    
}


bool MainCityScene::initWithID(int ID)
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(!CCScene::init());
        
        m_mainCityLayer = MainCityLayer::create(1);
        CC_BREAK_IF(!m_mainCityLayer);
        this->addChild(m_mainCityLayer);

        
        
        m_hudLayer = MainCityHudLayer::create();
        CC_BREAK_IF(!m_hudLayer);
        this->addChild(m_hudLayer);
        
        m_hudLayer->getDPad()->setDelegate(m_mainCityLayer);
        
        
        
        
        
        
		bRet = true;
	} while (0);

	return bRet;
}


