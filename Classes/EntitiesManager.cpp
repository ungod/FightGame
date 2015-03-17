#include "EntitiesManager.h"
class AnimationSprite;  

bool EntitiesManager::m_roleLock = false;

EntitiesManager::EntitiesManager()
{
    m_roleArray = Array::create();
    m_roleArray->retain();
    
    m_roleArrayToDelete = Array::create();
    m_roleArrayToDelete->retain();
    
	m_monstersNum = 0;
	m_playersNum = 0;
    init();

}

EntitiesManager::~EntitiesManager()
{
    removeAll();
    
    //log("delete RoleManager");

}

bool EntitiesManager::init()
{
    bool bRet = false;
    
    do {
       
        
        bRet = true;

    } while (0);
    
    return bRet;
}

void EntitiesManager::update()
{
    if(m_roleArrayToDelete->count() <= 0)
        return;
    
    Object* obj;
    CCARRAY_FOREACH_REVERSE(m_roleArrayToDelete, obj)
    {
       if(safaRemoveChild((Node*)obj))
       {
           m_roleArrayToDelete->removeObject(obj);
       }
    }
    
        
}



void EntitiesManager::addChild(Node* sprite)
{
    Layer* father = DataManager::getInstance()->getGameLayer();
    CCASSERT(father != NULL, "father layer is NULL");
    
    if(father == NULL || sprite == NULL)
        return;

    
    m_roleArray->addObject(sprite);
    father->addChild(sprite);

	Animate3D* anim3d = dynamic_cast<Animate3D*>(sprite);
	if (anim3d)
	{
		anim3d->setPosition3D(anim3d->getPosition3D());//刷新zorder
	}

	AnimationSprite* animSp = dynamic_cast<AnimationSprite*>(sprite);
	if (animSp)
	{
		if (animSp->getRoleFilter() == eRoleFilterPlayer)
		{
			m_playersNum++;
		}
		else if (animSp->getRoleFilter() == eRoleFilterMonster)
		{
			m_monstersNum++;
		}
	}

    //sprite->langding();//y不为0的时候滑落
}


void EntitiesManager::removeChild(Node* sprite)
{
    if (getRoleLock())
    {
        m_roleArrayToDelete->addObject(sprite);
    }
    
    else
    {
        forceRemoveChild(sprite);
    }
    

}


bool EntitiesManager::safaRemoveChild(Node* sprite)
{
    bool bRet = false;
    do {
        
        CC_BREAK_IF(getRoleLock());
        
        forceRemoveChild(sprite);
        
        bRet = true;
        
    } while (0);
    
    
    return bRet;
    
}




void EntitiesManager::forceRemoveChild(Node* sprite)
{
    ENTITIES_ROCKED;
    
	AnimationSprite* animsp = dynamic_cast<AnimationSprite*>(sprite);

	if (animsp)
	{
		animsp->stopSkills();
		animsp->onRemoved();
	}

	sprite->removeFromParentAndCleanup(true);
	m_roleArray->removeObject(sprite);

	if (animsp)
	{
		if (animsp->getRoleFilter() == eRoleFilterMonster)
		{
			m_monstersNum--;
			if (m_monstersNum <= 0)
			{
				if (DataManager::getInstance()->getGameLayer() != NULL)
				{
					DataManager::getInstance()->getGameLayer()->onMonsterClean();
				}
			}
		}

		if (animsp->getRoleFilter() == eRoleFilterPlayer)
		{
			m_playersNum--;
			if (m_playersNum <= 0)
			{
				if (DataManager::getInstance()->getGameLayer() != NULL)
				{
					DataManager::getInstance()->getGameLayer()->onPlayersClean();
				}
			}
		}
	}

    ENTITIES_UNLOCK;
}


void EntitiesManager::removeAll()
{
    if(m_roleArray->count() <= 0)//防止重复删除
        return;
    ENTITIES_ROCKED;
    
    Object* obj;
    CCARRAY_FOREACH_REVERSE(m_roleArray, obj)
    {
        Node* sprite = (Node*)obj;
        forceRemoveChild(sprite);
    }
    m_roleArray->removeAllObjects();
    CC_SAFE_RELEASE(m_roleArray);
    
    m_roleArrayToDelete->removeAllObjects();
    CC_SAFE_RELEASE(m_roleArrayToDelete);
    
    ENTITIES_UNLOCK;
}




Array* EntitiesManager::getRoleArray(EnumRoleFilter filter)
{
    if (getRoleLock())
    {
        return NULL;
    }
    
    
    ENTITIES_ROCKED;
    Array* pRet = Array::create();
    
    Object* obj;
    CCARRAY_FOREACH(getRoleArray(), obj)
    {
        AnimationSprite* sprite = dynamic_cast<AnimationSprite*>(obj);
        if(sprite && sprite->getRoleFilter() == filter)
        {
            pRet->addObject(sprite);
        }
    
    }
    
    ENTITIES_UNLOCK;
    return pRet;
}
















