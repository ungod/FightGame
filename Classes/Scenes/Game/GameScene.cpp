#include "DataManager.h"
#include "SKills/Actions/SkillMoveBy.h"
#include "Sqlite/SqliteHelper.h"
#include "Sqlite/SqliteResolver.h"
#include "Network/GameNet.h"
#include "CocoGUILIB/CocosGUIExamplesRegisterScene.h"
#include "Scenes/MainCity/MainCityScene.h"
#include "Scenes/Game/GameScene.h"

using namespace cocos2d;


GameScene* GameScene::create(int ID)
{ 
    GameScene *pRet = new GameScene(); 
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



GameScene::GameScene(void)
{
	m_gameLayer = NULL;
	m_hudLayer = NULL;
	m_bIsClose = false;
    DataManager::getInstance()->resetData();
	DataManager::getInstance()->setPhysicsEnable(true);
}

GameScene::~GameScene(void)//切换场景的时候可以用到
{
    NotificationCenter::getInstance()->removeAllObservers(this);//清除监听
    CC_SAFE_RELEASE(m_gameLayer);
    CC_SAFE_RELEASE(m_hudLayer);
    
    log("~GameScene");
    
}




bool GameScene::initWithID(int ID)
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(!CCScene::init());
        DataManager::getInstance()->setGameScene(this);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(STEEL_WHEEL_PLIST);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(STATUS_BAR_PLIST);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(NOTE_PLIST);
		TextureCache::getInstance()->addImage(GO_TIPS);
		
		m_hudLayer =  HudLayer::create();
		m_hudLayer->retain();
		this->addChild(m_hudLayer, 1);

        m_gameLayer = GameLayer::create(ID);
        m_gameLayer->retain();
		this->addChild(m_gameLayer, 0);

		m_hudLayer->getDPad()->setDelegate(m_gameLayer);
		m_gameLayer->setHud(m_hudLayer);
       
        //注册一条技能点击接收消息
        NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::onSkill), ON_SKILL_PRESS, NULL);
        
//        string s("切换");
//        LabelTTF *restartLabel = LabelTTF::create(s.c_str(), string("Times New Roman").c_str(), 25);
//        MenuItemLabel *restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_0(GameScene::switchGame,this));
//        Menu *menu = Menu::create(restartItem,  NULL);
//        menu->setAnchorPoint(Point(0,0));
//        menu->setPosition(Point( VisibleRect::rightBottom().x - restartItem->getContentSize().width ,VisibleRect::rightBottom().y + restartItem->getContentSize().height));
//        menu->setTag(5);
//        m_hudLayer->addChild(menu, 5);
        
        
        
        
        
        
		bRet = true;
	} while (0);

	return bRet;
}


void GameScene::switchGame(PortalSprite* pSender)
{
	if (m_bIsClose) return;

   
    int nextMapID = pSender->getNextMapID();
    m_bIsClose = true;
    m_gameLayer->unscheduleUpdate();
    DataManager::getInstance()->onSceneTrans();
    
    
    if(nextMapID <= 0)//最后一张地图,返回主城
    {
        MainCityScene* newScene = MainCityScene::create(1);
        CCDirector::getInstance()->replaceScene(newScene);
        
    }
    
    else//切换到下一张地图
    {
        TransitionScene* pTanScene = CCTransitionZoomFlipX::create(0.8f, GameScene::create(nextMapID));
        Director::getInstance()->replaceScene(pTanScene);
    }
	
}

void GameScene::onSkill(Object* pskillItem)
{
    //获取技能或者攻击点击的按键
    SkillItem* item = (SkillItem*)pskillItem;
    if(item->getTag() == e_skillBtattack)//攻击
    {
      m_gameLayer->getHero()->attack();
        
      //m_gameLayer->getMonsters()->onAttack();
      //CCLog("scene get attack");
    
    }
    
    else
    {
        Skill* pSkill = item->getSkill();
        m_gameLayer->getHero()->runSkill(pSkill);
    }
    
    if(item->getTag() == e_skillBt0)//技能
    {
        //GameNet* net = GameNet::getInstance();
       // net->test();
        
//        m_gameLayer->unscheduleUpdate();
//        DataManager::getInstance()->onSceneTrans();
//        CocosGUIExamplesMapScene* pScene = new CocosGUIExamplesMapScene();
//        pScene->runThisTest();
//        pScene->release();
        
        
        MainCityScene* newScene = MainCityScene::create(1);
        CCDirector::getInstance()->replaceScene(newScene);
        
      
    }
    
    
    
    /*
     if(item->getTag() == e_skillBt0 + 1)//技能
    {
       
        
    }
    
    if(item->getTag() == e_skillBt0 + 2)//技能
    {
             
    }*/


}



