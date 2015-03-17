#include "MainCityLayer.h"
#include "DataManager.h"
#include "Skills/Reader/RoleResolver.h"
#include "Sprites/Role/NPCSprite.h"
#include "../../Sprites/Entity/DungeonPortal.h"

USING_NS_CC;


MainCityLayer* MainCityLayer::create(int ID)
{ 
    MainCityLayer *pRet = new MainCityLayer(); 
    if (pRet && pRet->initWithID(ID))
    { 
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
    }
    
    return NULL; 
}



MainCityLayer::MainCityLayer(void)
{
    m_hero = NULL;
   
  
}

MainCityLayer::~MainCityLayer(void)//切换场景的时候可以用到
{
        
}

void MainCityLayer::initEntitiesManager()
{
	m_entitiesManager = new EntitiesManager();
	DataManager::getInstance()->setEntitiesManager(m_entitiesManager);
}


bool MainCityLayer::initWithID(int ID)
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(!BaseLayer::init());

		SqliteResolver* srl = SqliteResolver::create(TABLE_MAIN_CITY, ID);
		CC_BREAK_IF(!srl);

        initTileMap(srl->getInt("MapID"));
		initEntitiesManager();
        
        RoleResolver resolver;
        m_hero = resolver.createHero(1);
        CC_BREAK_IF(!m_hero);
		addChild(m_hero);

		m_hero->setPosition3D(m_hero->getPosition3D());

		Array* arr = srl->getArray("NPCs");

		Object* element;
		CCARRAY_FOREACH(arr, element)
		{
			Point3D pt = Point3DFromString(((String*)element)->getCString());
			NPCSprite* npc = NPCSprite::create(pt.z);
			addChild(npc);

			npc->setTarget(m_hero);
			npc->setPosition(Point(pt.x, pt.y));
		}

		arr = srl->getArray("Portals");
		CCARRAY_FOREACH(arr, element)
		{
			Point3D pt = Point3DFromString(((String*)element)->getCString());
			DungeonPortal* portal = DungeonPortal::create();
			addChild(portal);

			portal->setDungeonID(pt.z);
			portal->setTarget(m_hero);
			portal->setPosition(Point(pt.x, pt.y));
		}

        float tileWwidth = DataManager::getInstance()->getMapWidth();
        float tileHeight = DataManager::getInstance()->getMapHeight();
        auto followAction = Follow::create(m_hero,Rect(0, 0, tileWwidth, tileHeight));
        runAction(followAction);
        
		bRet = true;
	} while (0);

	return bRet;
}




void MainCityLayer::onDirectionChanged(Point direction)
{
    m_hero->walkWithDirection(direction);
}




void MainCityLayer::onKeepDirection(Point direction)
{
  m_hero->walkWithDirection(direction);

}




void MainCityLayer::onDirectionEnded()
{
    if (m_hero->getActionState() == kActionStateWalk)
	{
        m_hero->idle();
	}
}













