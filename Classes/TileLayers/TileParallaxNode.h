#pragma once
#include "cocos2d.h"
USING_NS_CC;


class TileParallaxNode : public ParallaxNode
{
public:
	TileParallaxNode(void);
	~TileParallaxNode(void);

	static TileParallaxNode* createWithID(int id);
    static TileParallaxNode * create(const char* tmxFile);
    static TileParallaxNode * create(TMXTiledMap* tileMap);
    bool init();
    
    CC_SYNTHESIZE_RETAIN(TMXTiledMap*, m_tileMap, TileMap);
    CC_SYNTHESIZE_READONLY(Layer*, m_floorLayer, FloorLayer);
    CC_SYNTHESIZE_READONLY(Layer*, m_nearWallLayer, NearWallLayer);//近景
    CC_SYNTHESIZE_READONLY(Layer*, m_middleWallLayer, MiddleWallLayer);//中层
    CC_SYNTHESIZE_READONLY(Layer*, m_farWallLayer, FarWallLayer);//远景层
    
    //CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapSize, MapSize);
    //CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tTileSize, TileSize);
    
    
    
};



