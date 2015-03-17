#include "SkillSystem.h"
#include "DataManager.h"
#include "cocos-ext.h"
#include <Box2D/Box2D.h>
#include "Sprites/Entity/SkillContactSprite.h"

USING_NS_CC_EXT;


class GameLayer;
class DataManager;
class RoleFilter;

SkillSystem* SkillSystem::create(const char* pFile)
{
    return NULL;
}

SkillSystem* SkillSystem::create(int ID)
{
    SkillSystem* pRet = new SkillSystem();
    if(pRet && pRet->initWithID(ID))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_RELEASE(pRet);
    pRet = NULL;
    
    return pRet;
}



SkillSystem::SkillSystem()
{
    m_skillArray = NULL;
}



SkillSystem::~SkillSystem()
{
   removeSkills();
   CC_SAFE_RELEASE(m_skillArray);

}


SkillSystem* SkillSystem::clone() const
{
    // no copy constructor
	auto skillSystem = new SkillSystem();
   	skillSystem->initWithSkillResolver(getSkillResolver());
	skillSystem->autorelease();
    skillSystem->setSkillItem(getSkillItem());
	return skillSystem;

}




bool SkillSystem::initWithID(int ID)
{
    bool bRet = false;
    do {
        SqliteResolver* resolver = SqliteResolver::create(TABLE_SKILLS, ID);
        CC_BREAK_IF(!resolver);
        initWithSkillResolver(resolver);
        
        bRet = true;
    } while (0);
    
    return bRet;

}


bool SkillSystem::initWithSkillResolver(SqliteResolver *resolver)
{
    bool bRet = false;
    do {
        
        m_skillArray = CCArray::create();
        CC_BREAK_IF(!m_skillArray);
        m_skillArray->retain();
        
        Skill::initWithSkillResolver(resolver);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void SkillSystem::onStarted()
{
    if(m_pOwner != NULL)
    {
        
        Object* obj = NULL;
        Array* hitBoxes = getSkillResolver()->getArray("HitBoxIDs");
        CCARRAY_FOREACH(hitBoxes, obj)//创建碰撞框
        {
            int hitBoxID = ((String*)obj)->intValue();
            //log("hitBoxID %d",hitBoxID);
            
            SkillContactSprite* sprite = SkillContactSprite::create(hitBoxID);
            CCAssert(sprite != NULL, "ContactSprite is NULL");
            
            if(getOwner()->getFaceDirection().x < 0)//修改朝向方向
            {
                sprite->setScaleX(-1.0f);
            }
            addSkill(sprite);
        }
        
        getOwner()->playAnimation(getAnimationName().c_str());//运行动画
        
     
        if(getAttackMotionCurve() != NULL)
        {
          getOwner()->runSequanceAction(getAttackMotionCurve());//设定运动轨迹
        }
              
        MusicPlayer* musiPlayer = MusicPlayer::getInstance();
        if(musiPlayer != NULL)//播放音乐
        {
            musiPlayer->playEffect(m_skillMusicID);
        }
    }
}


void SkillSystem::addSkill(SkillContactSprite* child)
{
    Node* father = DataManager::getInstance()->getGameLayer();
    
    child->setSkillParent(this);//设定技能父类
    
    father->addChild(child,getOwner()->getZOrder());
    m_skillArray->addObject(child);
    
    FiniteTimeAction* actionSequance = Sequence::create(DelayTime::create(child->getDelayTime()),
                                                        CallFunc::create( CC_CALLBACK_0(ContactSprite::onStarted,child)),//启动
                                                        DelayTime::create(child->getDuration()),
                                                        CallFunc::create( CC_CALLBACK_0(SkillSystem::removeSkill, this, child)),//生命时间
                                                        NULL);
    child->runAction(actionSequance);//生命周期完成设定回调


}

void SkillSystem::removeSkill(SkillContactSprite* child)
{
    child->onFinished();
    
    m_skillArray->removeObject(child);
    if(m_skillArray->count() == 0)
    {
        onFinished();
    }

}


void SkillSystem::removeSkills()
{
    Object* obj;
    
    CCARRAY_FOREACH_REVERSE(m_skillArray, obj)
    {
        SkillContactSprite* child = (SkillContactSprite*) obj;
        removeSkill(child);
    }
    
}


void SkillSystem::onFinished()//技能完成
{
   
    if(m_callbackTarget && m_pFuncSelector )
    {
        (m_callbackTarget->*m_pFuncSelector)(this);//通知owner移除
    
    }
    
}

void SkillSystem::onCollsion(SkillContactSprite* pSender, AnimationSprite* pTarget)
{
    if(pTarget->getActionState() != kActionStateKnockedOut)
    {
        int hitNum = pSender->getHitMaxNum() - 1;
        pSender->setHitMaxNum(hitNum);
        pSender->onCollsion(pTarget);
    }
      
}












