#pragma once
#include "cocos2d.h"
#include "Hud/DirectionPad.h"
#include "Physics/PhysicsWorld.h"
#include "TileLayers/TileParallaxNode.h"
#include "TileLayers/DebugLayer.h"


#define OBJECT_NEAR_TAG  500
#define OBJECT_MIDDLE_TAG 501
#define OBJECT_FAR_TAG 502

class EntitiesManager;
class PortalSprite;

class BaseLayer : public cocos2d::Layer, public DirectionPadDelegate
{
public:
    
	BaseLayer(void);
	~BaseLayer(void);
    
    virtual bool init();
    
	bool initTileMap(int ID);
    void initPhysicsWorld();

    
	virtual void onDirectionChanged(Point direction);
	virtual void onKeepDirection(Point direction);
	virtual void onDirectionEnded();

    
    void onExit();
    
    virtual void tick(float dt);//box2d使用
    virtual void onSceneTrans();//场景将要切换的时候,用来回收资源


    float CaculateObjectMiddleOrder();//计算中间层的zorder;
       

    
    CC_SYNTHESIZE(Layer*, m_objectsNear, ObjectsNear);
    CC_SYNTHESIZE(Layer*, m_objectsMiddle, ObjectsMiddle);
    CC_SYNTHESIZE(Layer*, m_objectsFar, ObjectsFar);
    CC_SYNTHESIZE(TileParallaxNode*, m_tileParallaxNode, ParallaxNode);
    CC_SYNTHESIZE(DebugLayer*, m_debugLayer, DebugLayer);
    CC_SYNTHESIZE(PhysicsWorld*, m_physicsWorld, PhysicsWorld);//物理世界



};
