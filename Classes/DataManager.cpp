#include "DataManager.h"
#include "VisibleRect.h"
#include "EntitiesManager.h"
#include "Network/GameNet.h"

static DataManager* s_pDataInstance = NULL;

DataManager::DataManager()
{
	m_bPhysicEnable = true;
   resetData();
}


DataManager::~DataManager()
{
    CC_SAFE_DELETE(s_pDataInstance);

}

void DataManager::resetData()
{
    m_floorTop = 250;
    m_floorBottom = 32;
    m_maxZorder = VisibleRect::top().y;
    
    m_heroID = 1;
    
    m_gameLayer = NULL;
    m_gameScene = NULL;
    m_hudLayer = NULL;
    m_roleManager = NULL;
    
    m_physicsWorld = NULL;
    
    log("DataManager reset");

}


void DataManager::onSceneTrans()
{
   // m_gameLayer->getEntitiesManager()->removeAll();
    m_gameLayer->onSceneTrans();
    GameNet::getInstance()->stopNet();
}

 DataManager* DataManager::getInstance()
{
    
  if(NULL == s_pDataInstance )
  {
      s_pDataInstance = new DataManager();
      
      s_pDataInstance->init();
  
  }

    return s_pDataInstance;
}



bool DataManager::init()
{
    bool bRet = false;

    do {
        
        
        bRet = true;
        
    } while (0);
    
    
    
    return bRet;
}