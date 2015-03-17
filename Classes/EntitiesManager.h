#pragma once

#include "cocos2d.h"
#include "DataManager.h"
USING_NS_CC;

/*角色与实体的统一管理的类
 
 */
class EntitiesManager;

#define ENTITIES_ROCKED EntitiesManager::setRoleLock(true)
#define ENTITIES_UNLOCK EntitiesManager::setRoleLock(false)

class EntitiesManager
{
public:
    EntitiesManager();
    ~EntitiesManager();
   
    
    bool init();
    virtual void update();
    
    void removeAll();
    void addChild(Node* sprite);
    void removeChild(Node* sprite);
    bool safaRemoveChild(Node* sprite);//安全删除
    void forceRemoveChild(Node* sprite);//强制删除
    
    Array* getRoleArray(EnumRoleFilter filter);
    
    CC_SYNTHESIZE(Array*, m_roleArray, RoleArray);//保存各类角色的数组
    CC_SYNTHESIZE(Array*, m_roleArrayToDelete, RoleArrayToDelete);//要删除的角色队列

	CC_SYNTHESIZE_READONLY(int, m_monstersNum, MonstersNum);
	CC_SYNTHESIZE_READONLY(int, m_playersNum, PlayersNum);
   
    //@brief 角色锁
    //使用意义:对角色队列操作的时候防止删除操作造成野指针
    static bool m_roleLock;
    static bool getRoleLock(){return m_roleLock;}
    static void setRoleLock(bool lock){m_roleLock = lock;}
    
    
    

	
};




