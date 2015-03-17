#include "GameLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "EntitiesManager.h"
#include "Skills/Reader/RoleResolver.h"
#include "Skills/Reader/RoleResolver.h"
#include "Sprites/Role/AiPlayer.h"
#include "Sprites/AnimationSprite.h"
#include "DataInfo/PropResolver.h"
#include "Sprites/Entity/ItemSprite.h"
#include "Sprites/Entity/PortalSprite.h"
#include "Sprites/Entity/BarrierSprite.h"
using namespace  std;


GameLayer::GameLayer(void)
{
    m_birds = NULL;
    m_hero = NULL;
    m_entitiesManager = NULL;
    m_leavesBatch = NULL;
    m_monstersLoader = NULL;
    
    m_followAction = NULL;
	m_sqliteResolver = NULL;
	m_boss = NULL;
	m_protal = NULL;
}

GameLayer::~GameLayer(void)
{
    log("exit gamelayer");
    m_sqliteResolver->release();

	//CC_SAFE_RELEASE(m_protal);
}


void GameLayer::onExit()
{
    //CCLayer::onExit();
    CC_SAFE_RELEASE(m_leavesBatch);
        
   // armature::CCArmatureDataManager::sharedArmatureDataManager()->removeAll();
    log("gamelayer onSceneTrans()");
    
    BaseLayer::onExit();
 }


void GameLayer::onSceneTrans()
{
    BaseLayer::onSceneTrans();
    CC_SAFE_DELETE(m_entitiesManager);
    CC_SAFE_RELEASE(m_monstersLoader);
}


GameLayer* GameLayer::create(int ID)
{
    GameLayer *pRet = new GameLayer();
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

bool GameLayer::initWithID(int ID)
{
    bool bRet = false;
	do
	{
        CC_BREAK_IF(!BaseLayer::init());
        
        m_sqliteResolver = SqliteResolver::create(TABLE_SCENES, ID);
        CC_BREAK_IF(!m_sqliteResolver);
        
        DataManager::getInstance()->setGameLayer(this);
        int mapID = m_sqliteResolver->getInt("MapID");
        CC_BREAK_IF(!initTileMap(mapID)) ;
        
    
        string musicPath = m_sqliteResolver->getString("BackgroundMusic");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicPath.c_str());
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicPath.c_str(),true);
        
        
        initEntitiesManager();
        
        int monstersID = m_sqliteResolver->getInt("MonstersID");
               m_monstersLoader = MonstersLoader::create(monstersID);
        CC_BREAK_IF(!m_monstersLoader);
        m_monstersLoader->retain();

        Array* monsterArray = m_monstersLoader->getMonstersGroup();
        addMonsterGroup(monsterArray);
        
        CC_BREAK_IF(!initHero(DataManager::getInstance()->getHeroID()));
        Point heroPos = m_sqliteResolver->getPoint("PlayerPosition");
        m_hero->setPosition3D(Point3D(heroPos.x,0,heroPos.y));

        m_sqliteResolver->retain();
        initItems();
        
        
        
        setTouchEnabled(true);
        Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
        //调度任务
        this->scheduleUpdate();
        
		bRet = true;
	} while (0);
    
    
    return  bRet;
}







void GameLayer::initLeaves()//初始化落叶
{
    
    ParticleSystem* m_emittor;
    m_emittor = CCParticleSystemQuad::create("leaves.plist");
    m_emittor->setPosition(Point(CENTER.x,CENTER.y * 2));
    m_leavesBatch = CCParticleBatchNode::createWithTexture(m_emittor->getTexture());
    m_leavesBatch->addChild(m_emittor);
    
    for( int i = 0; i < 4; i++)
    {
        ParticleSystem* m_emittor;
        m_emittor = CCParticleSystemQuad::create("leaves.plist");
        m_emittor->setPosition(Point(CENTER.x + ( i + 1) * 400,CENTER.y * 2));
        m_leavesBatch->addChild(m_emittor);
        
    }
    m_tileParallaxNode->getNearWallLayer()->addChild(m_leavesBatch,0,0);//leaves
    
    
    
}

void GameLayer::initBirds()//初始化小鸟
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("birds.plist");
    m_birds = CCSpriteBatchNode::create("birds.png");
    CCAssert(m_birds != NULL, "Birds create error!");
    m_birds->getTexture()->setAliasTexParameters();
    m_birds->setAnchorPoint(Point::ZERO);
    m_birds->setPosition(Point(0,0));
    m_tileParallaxNode->getFarWallLayer()->addChild(m_birds, 1);
    
    Array *flyFrames = Array::createWithCapacity(8);
    int i = 0;
    int frameNum = 7;
    for (i = 0; i <= frameNum; i++)
    {
        SpriteFrame *frame = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("bird1-1_%d.png",i)->getCString());
        flyFrames->addObject(frame);
    }
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(flyFrames,float(1.0 / 24.0* CCRANDOM_0_1() + 1.0 /12.0));
    float maxX = DataManager::getInstance()->getMapWidth();
    for(i = 0; i < 10; i++)
    {
        Sprite* birds = CCSprite::createWithSpriteFrameName("bird1-1_0.png");
        m_birds->addChild(birds);
        birds->setScale(1.6f);
        float x = CCRANDOM_0_1() * maxX;
        float y = VisibleRect::top().y -  CCRANDOM_0_1() * 350;
        birds->setPosition(Point(x,y));
        birds->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        
    }
}




void GameLayer::initEntitiesManager()
{
    m_entitiesManager = new EntitiesManager();
    DataManager::getInstance()->setEntitiesManager(m_entitiesManager);
}

void GameLayer::initItems()
{
	for (int i=0; i<10; i++)
	{
		//掉落道具
		ItemSprite* item = ItemSprite::createWithAnimationID(1, "explo");
		item->setPosition(Point(rand()%2000, rand()%100 + 100));
		getEntitiesManager()->addChild(item);
	}
	for (int i=0; i<3; i++)
	{
		//障碍物
		BarrierSprite* item = BarrierSprite::create();
		item->setPosition(Point(rand()%2000, rand()%100 + 100));
		getEntitiesManager()->addChild(item);
	}
}

bool GameLayer::initHero(int ID)//初始化角色
{
    bool bRet = false;
    
    do {
        RoleResolver resolver;
        Hero* hero = resolver.createHero(ID);
        CC_BREAK_IF(!hero);
        setHero(hero);
        getEntitiesManager()->addChild(m_hero);
		DataManager::getInstance()->getHudLayer()->createHeroBar();
        
        bRet = true;
    } while (0);
    
    
    return bRet;
}

void GameLayer::onDirectionChanged(Point direction)
{
    m_hero->walkWithDirection(direction);
}

void GameLayer::onKeepDirection(Point direction)
{
    m_hero->walkWithDirection(direction);
    
}

void GameLayer::onDirectionEnded()
{
	if (m_hero->getActionState() == kActionStateWalk)
	{
        m_hero->idle();
	}
}


void GameLayer::updateHud()
{
	if (m_protal)
	{
		Point pt = Point(m_protal->getX(), 0);
		Point cpt = convertToWorldSpace(pt);

		if (cpt.x <= Director::getInstance()->getWinSize().width)
		{
			DataManager::getInstance()->getHudLayer()->setPortalTipsVisible(false);
		}
	}
}

void GameLayer::update(float dt)
{
    m_hud->getDPad()->update(dt);
    m_entitiesManager->update();

	updateHud();
}

void GameLayer::setHero(Hero* hero)
{
  if(hero == NULL || hero == m_hero)
      return;
    
  if(getFollowAction() != NULL)
  {
      stopAction(getFollowAction());
  }
    
    m_hero = hero;
    float tileWwidth = DataManager::getInstance()->getMapWidth();
    float tileHeight = DataManager::getInstance()->getMapHeight();
    m_followAction = Follow::create(hero,Rect(0, 0, tileWwidth, tileHeight));
    runAction(m_followAction);
}

bool GameLayer::ccTouchBegan(Touch *touch, Event *event)
{
//    Point location = convertToNodeSpace(touch->getLocation()) ;
//    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
//    
//    if(getEntitiesManager() == NULL)
//        return false;
//    
//    Array* array = getEntitiesManager()->getRoleArray();
//    Object* obj;
//    CCARRAY_FOREACH(array, obj)
//    {
//        AnimationSprite* sprite = (AnimationSprite*)obj;
//        b2Fixture* fixture = sprite->getBody()->GetFixtureList();
//       if (fixture->TestPoint(locationWorld))
//       {
//                
//         log("sprite");
//         setHero(sprite);
//         return true;
//       }
//    }
    
    return false;
}


void  GameLayer::addMonsterGroup(Array* monsterArray)
{
    Object* obj;
    CCARRAY_FOREACH(monsterArray, obj)
    {
        MonstersLoaderData* pData = (MonstersLoaderData*)obj;
        
        RoleResolver resolver;
        AiPlayer* aiSprite = resolver.createAiPlayer(pData->getID());
        if(aiSprite == NULL)
            continue;
        
        getEntitiesManager()->addChild(aiSprite);
        aiSprite->setPosition3D(pData->getPosition());

		MonsterProp* prop = (MonsterProp*)aiSprite->getRoleProperty();

		if (prop->getType() == 1)
		{
			setBoss(aiSprite);
			DataManager::getInstance()->getGameScene()->getHudLayer()->createBossBar();
		}

       // log("%f %f  ID %d",pData->getPosition().x,pData->getPosition().z,pData->getID());
        
    }

}



void GameLayer::onMonsterClean()
{
    
    Array* monsterGroup =  m_monstersLoader->getMonstersGroup();
    if (monsterGroup != NULL)
    {
        addMonsterGroup(monsterGroup);
        
    }
    
    else//怪物消灭完成
    {
		m_protal =  PortalSprite::createWithID(m_sqliteResolver->getInt("PortalAnimationID"));
		if (m_protal)
		{
			m_protal->setPosition(m_sqliteResolver->getPoint("PortalPosition"));
            m_protal->setNextMapID(m_sqliteResolver->getInt("NextMapID"));
			getEntitiesManager()->addChild(m_protal);
			DataManager::getInstance()->getHudLayer()->setPortalTipsVisible(true);
		}
    }
	
}

void GameLayer::onPlayersClean()
{

}










