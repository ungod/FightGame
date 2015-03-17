#pragma once
#include "cocos2d.h"
#include "HudLayer.h"
#include "Hud/DirectionPad.h"
#include "Sprites/Role/Hero.h"
#include "Physics/PhysicsWorld.h"
#include "TileLayers/TileParallaxNode.h"
#include "TileLayers/DebugLayer.h"
#include "Loader/MonstersLoader.h"
#include "../Base/BaseLayer.h"


class EntitiesManager;
class PortalSprite;

class GameLayer : public BaseLayer
{
public:
    
    static GameLayer* create(int ID);
    
	GameLayer(void);
	~GameLayer(void);
    
    virtual bool initWithID(int ID);
    
	bool initHero(int ID);
    void initBirds();
    void initLeaves();//落叶
	void initItems();
    void initEntitiesManager();
    
	virtual void onDirectionChanged(Point direction);
	virtual void onKeepDirection(Point direction);
	virtual void onDirectionEnded();

	virtual void onMonsterClean();//当前场景怪物已清除
	virtual void onPlayersClean();//当前所有玩家已死亡
   
    void onExit();

	void update(float dt);
    void addMonsterGroup(Array* monsterArray);
    void onSceneTrans();//场景将要切换的时候,用来回收资源
	void updateHud();
    
    SpriteBatchNode *m_birds;
    ParticleBatchNode * m_leavesBatch;

    virtual Hero* getHero(){return m_hero;}
    virtual void setHero(Hero* hero);
    
    CC_SYNTHESIZE(AnimationSprite*, m_boss, Boss);
    
    
    CC_SYNTHESIZE(EntitiesManager*, m_entitiesManager, EntitiesManager);//角色管理
	CC_SYNTHESIZE(HudLayer*, m_hud, Hud);
    CC_SYNTHESIZE(Follow*, m_followAction, FollowAction);//镜头跟随动作
    CC_SYNTHESIZE(MonstersLoader*, m_monstersLoader, MonstersLoader);
	CC_SYNTHESIZE(SqliteResolver*, m_sqliteResolver, SqliteResolver);
    
    virtual bool ccTouchBegan(Touch *touch, Event *event);
     
protected:
    Hero* m_hero;
	PortalSprite* m_protal;
};
