#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "Scenes/Game/GameLayer.h"
#include "Scenes/Game/GameScene.h"
#include "Scenes/Game/HudLayer.h"


/***作为数值管理使用**********/


class DataManager
{
public:
    DataManager();
    ~DataManager();
    static DataManager* getInstance();
    bool init();
    void resetData();//重置数值
    void onSceneTrans();//场景切换之前调用
    
    CC_SYNTHESIZE(float, m_floorTop, FloorTop);//角色在地图行走的上边界
    CC_SYNTHESIZE(float, m_floorBottom, FloorBottom);//角色在地图行走的下边界
    CC_SYNTHESIZE(float, m_maxZorder, MaxZorder);//地图上行走的角色的最大zorder值
    CC_SYNTHESIZE(float, m_mapWidth, MapWidth);//地图的宽度
    CC_SYNTHESIZE(float, m_mapHeight, MapHeight);//地图的宽度
    CC_SYNTHESIZE(Size, m_mapSize, MapSize);//地图的块数量
    CC_SYNTHESIZE(Size, m_tileSize, TileSize);//地图每块的大小(像素)
    
    
    CC_SYNTHESIZE(GameLayer*, m_gameLayer, GameLayer);
    CC_SYNTHESIZE(GameScene*, m_gameScene, GameScene);
    CC_SYNTHESIZE(HudLayer*, m_hudLayer, HudLayer);
    CC_SYNTHESIZE(EntitiesManager*, m_roleManager, EntitiesManager);
    
    
    CC_SYNTHESIZE(int, m_heroID, HeroID);
    
    CC_SYNTHESIZE(PhysicsWorld*, m_physicsWorld, PhysicsWorld);//物理世界
	CC_SYNTHESIZE(bool, m_bPhysicEnable, PhysicsEnable);
};


