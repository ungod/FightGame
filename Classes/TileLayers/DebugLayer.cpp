#include "DebugLayer.h"
#include "cocos2d.h"
#include "../Physics/PhysicsWorld.h"
#include "DataManager.h"
USING_NS_CC;

DebugLayer::DebugLayer()
{
    
}


DebugLayer::~DebugLayer()
{
    
}

DebugLayer* DebugLayer::create()
{
    DebugLayer* pRet =new DebugLayer();
    if(pRet && pRet->init())
       {
        
           pRet->autorelease();
       }
       
       return pRet;
}


bool DebugLayer::init()
{
    bool bRet = false;
    do {
        
        
        
        bRet = true;
    } while (0);

    return bRet;
}


void DebugLayer::draw()
{
    //CCNode::draw();
    //CCLog("node draw");
    DataManager::getInstance()->getPhysicsWorld()->drawDebug();

}
