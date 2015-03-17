#include "Skill.h"

#include "Skills/Reader/RoleResolver.h"

class Point3D;

Skill::Skill()
{
  m_skillName = "";
  m_animationName = "";
  m_skillIcon = "";
  m_skillIconDisabled = "";
  m_skillMusicID = 0;
  m_skillFollow = false;
    
    
  m_pOwner = NULL;
  m_direction = Point(0,0);
  m_pFuncSelector = NULL;
  m_callbackTarget = NULL;
  m_attackMotionCurve = NULL;
  m_skilItem = NULL;
  m_resolver = NULL;

  
}



Skill::~Skill()
{
    CC_SAFE_RELEASE(m_resolver);
    //log("Skill::~Skill()");
}





bool Skill::initWithSkillResolver(SqliteResolver *resolver)
{
    bool bRet = false;
    
    do
    {

        setSkillResolver(resolver);
        
        m_skillName = resolver->getString("SkillName");
        //log("m_skillName:%s",m_skillName.c_str());
        
        int followFlag = resolver->getInt("SkillFollow");
        m_skillFollow = (bool) followFlag;
       // log("m_skillFollow:%d",m_skillFollow);
        
        m_animationName = resolver->getString("AnimationName");
        //log("AnimationName:%s",m_animationName.c_str());
        
        m_skillIcon = FileUtils::getInstance()->fullPathForFilename(resolver->getString("SkillIcon").c_str());
       // log("SkillIcon:%s",m_skillIcon.c_str());
        
        m_skillIconDisabled = FileUtils::getInstance()->fullPathForFilename(resolver->getString("SkillIconDisabled").c_str());
        //log("SkillIconDisabled:%s",m_skillIconDisabled.c_str());
        
        
        m_skillMusicID = resolver->getInt("SkillMusicID");
        MusicPlayer* musiPlayer = MusicPlayer::getInstance();
        if(musiPlayer != NULL)
        {
            musiPlayer->preloadEffect(m_skillMusicID);
        }
        //log("SkillMusic:%s",m_skillMusic.c_str());
        
        m_skillMPConsume = resolver->getInt("SkillMPConsume");
        m_skillHitJudgement = resolver->getInt("SkillHitJudgement");
        //log("SkillMPConsume:%d  SkillHitJudgement:%d",m_skillMPConsume,m_skillHitJudgement);
        
        m_skillCondition = resolver->getInt("SkillCondition");
        m_skillPlace = resolver->getInt("SkillPlace");
        //log("SkillCondition:%d SkillPlace:%d",m_skillCondition,m_skillPlace);
        
        m_attackMotionCurve = resolver->getPoint3DSequance("OnAttackMotionCurve");
        
        
        m_aiDistance = resolver->getPoint("AiDistance");
        //log("m_aiDistance x:%f z:%f",m_aiDistance.x, m_aiDistance.y );
        
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}





void Skill::startSkillWithOwner(AnimationSprite* pOwner, Point direction)
{
    setOwner(pOwner);
    setDirection(direction);
    this->onStarted();

}


void Skill::setFinishedCallback(Node* pTarget, SEL_CallFuncO selector)
{
    m_callbackTarget = pTarget;
    m_pFuncSelector = selector;
}

void Skill::onCollsion(SkillContactSprite* pSender, AnimationSprite* pTarget)
{

}




