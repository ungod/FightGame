#include "BaseLayer.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "Sprites/AnimationSprite.h"

using namespace  std;


BaseLayer::BaseLayer(void)
{
    m_tileParallaxNode = NULL;
    m_debugLayer = NULL;


    
    m_objectsFar = CCLayer::create();
    m_objectsFar->retain();
    
    m_objectsMiddle = CCLayer::create();
    m_objectsMiddle->retain();
    
    m_objectsNear = CCLayer::create();
    m_objectsNear->retain();
    
    m_physicsWorld = NULL;
    
    

}

BaseLayer::~BaseLayer(void)
{
    log("exit BaseLayer");
    CC_SAFE_RELEASE(m_tileParallaxNode);
    CC_SAFE_RELEASE(m_objectsFar);
    CC_SAFE_RELEASE(m_objectsMiddle);
    CC_SAFE_RELEASE(m_objectsNear);
	
}


void BaseLayer::onExit()
{
    CCLayer::onExit();
    CC_SAFE_DELETE(m_physicsWorld);
    log("BaseLayer onSceneTrans()");
    unscheduleAllSelectors();
    Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
}


void BaseLayer::onSceneTrans()
{
    

}



bool BaseLayer::init()
{
    bool bRet = false;
	do
	{
        CC_BREAK_IF(!CCLayer::init());
        
        
        
        initPhysicsWorld();//初始化物理世界
        
        m_debugLayer = DebugLayer::create();//调试使用的层
        m_debugLayer->retain();
        addChild(m_debugLayer,DataManager::getInstance()->getMaxZorder()+ 1);
        
        
        
		bRet = true;
	} while (0);
    
    
    return  bRet;
}





void BaseLayer::initPhysicsWorld()
{
    
    m_physicsWorld = PhysicsWorld::create();
    DataManager::getInstance()->setPhysicsWorld(m_physicsWorld);
    schedule(schedule_selector(BaseLayer::tick));
    
}


void BaseLayer::tick(float dt)
{
    getPhysicsWorld()->update(dt);
}




float BaseLayer::CaculateObjectMiddleOrder()//计算中间层中的阻挡关系
{
    int maxX = DataManager::getInstance()->getMapSize().width;
    int maxY = DataManager::getInstance()->getMapSize().height;
    float ret = 0;
    for(int x = 0; x < maxX; x++)
    {
        float zorder = 0;
        for(int y = maxY - 1; y >= 0; y--)
        {
            Sprite* sprite = ((TMXLayer*)m_objectsMiddle->getChildByTag(OBJECT_MIDDLE_TAG))->getTileAt(Point(x,y));
            if(sprite != NULL)
            {
                zorder = DataManager::getInstance()->getMaxZorder() - sprite->getPosition().y;//检索最大的zorder
                if(zorder > ret)
                {
                    ret = zorder;
                }
            }
        }
    }
    
    return ret;
}





bool BaseLayer::initTileMap(int ID)//初始化地图
{
    bool bRet = false;
    
    do {
        m_tileParallaxNode = TileParallaxNode::createWithID(ID);
        
        CCAssert(m_tileParallaxNode != NULL, "TileParallaxNode cannot be NULL");
        CC_BREAK_IF(!m_tileParallaxNode);
        
        m_tileParallaxNode->retain();
        addChild(m_tileParallaxNode, 0, -6);
        
        
        TMXTiledMap* pTileMap = m_tileParallaxNode->getTileMap();
        TMXLayer *tmxLayer;
        tmxLayer = pTileMap->getLayer("ObjectsFar");
        CCAssert(tmxLayer != NULL, "ObjectsFar layer not found!");
        tmxLayer->retain();
        tmxLayer->removeFromParentAndCleanup(false);
        m_objectsFar->addChild(tmxLayer, 0, OBJECT_FAR_TAG);
        addChild(m_objectsFar);
        tmxLayer->release();
        
        tmxLayer = pTileMap->getLayer("ObjectsMiddle");
        CCAssert(tmxLayer != NULL, "ObjectsMiddle layer not found!");
        tmxLayer->retain();
        tmxLayer->removeFromParentAndCleanup(false);
        m_objectsMiddle->addChild(tmxLayer);
        tmxLayer->setTag(OBJECT_MIDDLE_TAG);
        addChild(m_objectsMiddle, CaculateObjectMiddleOrder(),OBJECT_MIDDLE_TAG);
        //reorderTMXLayer(tmxLayer);//这样渲染批次有点高
        tmxLayer->release();
        
        tmxLayer = pTileMap->getLayer("ObjectsNear");
        CCAssert(tmxLayer != NULL, "ObjectsNear layer not found!");
        tmxLayer->retain();
        tmxLayer->removeFromParentAndCleanup(false);
        m_objectsNear->addChild(tmxLayer,0,OBJECT_NEAR_TAG);
        addChild(m_objectsNear);
        tmxLayer->release();
        
        reorderChild(m_objectsFar, 0);//reorder the layer
        reorderChild(m_objectsNear, DataManager::getInstance()->getMaxZorder() + 1);
        
        
        bRet = true;
    } while (0);
    
    return  bRet;
    
}







void BaseLayer::onDirectionChanged(Point direction)
{
    
}

void BaseLayer::onKeepDirection(Point direction)
{
   
    
}

void BaseLayer::onDirectionEnded()
{
	
}



















