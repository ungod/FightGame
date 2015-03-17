#include "TileParallaxNode.h"
#include "../DataManager.h"


TileParallaxNode::TileParallaxNode(void)
{
    m_tileMap = NULL;
    m_floorLayer = CCLayer::create();
    m_floorLayer->retain();
    
    m_nearWallLayer = CCLayer::create();
    m_nearWallLayer->retain();
    
    m_middleWallLayer = CCLayer::create();
    m_middleWallLayer->retain();
    
    m_farWallLayer = CCLayer::create();
    m_farWallLayer->retain();
    
}



TileParallaxNode::~TileParallaxNode(void)
{
    CC_SAFE_RELEASE(m_tileMap);
    CC_SAFE_RELEASE(m_floorLayer);
    CC_SAFE_RELEASE(m_nearWallLayer);
    CC_SAFE_RELEASE(m_middleWallLayer);
    CC_SAFE_RELEASE(m_farWallLayer);
}

TileParallaxNode* TileParallaxNode::createWithID( int id )
{
	TileParallaxNode* pRet = new TileParallaxNode();

	SqliteResolver* resolver = SqliteResolver::create(TABLE_MAPS, id);
	if (!resolver)
		return NULL;

	pRet->m_tileMap = CCTMXTiledMap::create(resolver->getString("TMXFilePath").c_str());
	CCAssert(pRet->m_tileMap != NULL, "TMXTiledMap should not be NULL");

	if(pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;

	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

TileParallaxNode* TileParallaxNode::create(const char* tmxFile)
{
    TileParallaxNode* pRet = new TileParallaxNode();
    pRet->m_tileMap = CCTMXTiledMap::create(tmxFile);
    CCAssert(pRet->m_tileMap != NULL, "TMXTiledMap should not be NULL");
    
    if(pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
        
    }
    
    
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
    
}


TileParallaxNode * TileParallaxNode::create(TMXTiledMap* tileMap)
{
    TileParallaxNode* pRet = new TileParallaxNode();
    pRet->m_tileMap = tileMap;
    if(pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
        
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}


bool TileParallaxNode::init()
{
    
    if(! m_tileMap)
    {
        return false;
    }
    
    m_tileMap->retain();
    TMXLayer* tmxLayer = m_tileMap->getLayer("NearWall");
    CCAssert(tmxLayer != NULL, "NearWall layer not found!");
    tmxLayer->retain();
    tmxLayer->removeFromParentAndCleanup(false),
    m_nearWallLayer->addChild(tmxLayer, 0);
    addChild(m_nearWallLayer, 0, Point(1.0f,1.0f), Point(0,0) );
    tmxLayer->release();

    
    tmxLayer = m_tileMap->getLayer("MiddleWall");
    CCAssert(tmxLayer != NULL, "MiddleWall layer not found!");
    tmxLayer->retain();
    tmxLayer->removeFromParentAndCleanup(false),
    m_middleWallLayer->addChild(tmxLayer, 0);
    addChild(m_middleWallLayer, -1, Point(0.80f,1.0f), Point(0,0) );
    tmxLayer->release();
    
    
    tmxLayer = m_tileMap->getLayer("Floor");
    CCAssert(tmxLayer != NULL, "Floor layer not found!");
    tmxLayer->retain();
    String* floorTop = tmxLayer->getProperty("top");//获取上边界
    if(floorTop != NULL)
    {
        DataManager::getInstance()->setFloorTop(floorTop->intValue());
    }
    
    String* floorBottom = tmxLayer->getProperty("bottom");//获取下边界
    if(floorBottom != NULL)
    {
         DataManager::getInstance()->setFloorBottom(floorBottom->intValue());
    }
    tmxLayer->removeFromParentAndCleanup(false),
    m_floorLayer->addChild(tmxLayer, 0);
    addChild(m_floorLayer, -2,  Point(1.0f,1.0f), Point(0,0) );
    tmxLayer->release();
    
    
    
    
    tmxLayer = m_tileMap->getLayer("FarWall");
    CCAssert(tmxLayer != NULL, "FarWall layer not found!");
    tmxLayer->retain();
    tmxLayer->removeFromParentAndCleanup(false),
    m_farWallLayer->addChild(tmxLayer, 0);;
    addChild(m_farWallLayer, -3, Point(0.65f,1.0f), Point(0,0));
    tmxLayer->release();
   
    
    
    
    DataManager::getInstance()->setTileSize(m_tileMap->getTileSize());
    DataManager::getInstance()->setMapSize(m_tileMap->getMapSize());
   
    
    float mapWidth = m_tileMap->getTileSize().width * m_tileMap->getMapSize().width;
    float mapHeight = m_tileMap->getTileSize().height * m_tileMap->getMapSize().height;
    DataManager::getInstance()->setMapWidth(mapWidth);
    DataManager::getInstance()->setMapHeight(mapHeight);
    
    
    
    return true;
}