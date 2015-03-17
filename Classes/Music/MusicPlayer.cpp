#include "MusicPlayer.h"


static MusicPlayer* s_musicPlayer = NULL;

MusicPlayer* MusicPlayer::getInstance()
{
  if(s_musicPlayer == NULL)
  {
      MusicPlayer* pRet = new MusicPlayer();
      
      if( pRet && pRet->init())
      {
          s_musicPlayer = pRet;
          return pRet;
          
      }

      CC_SAFE_RELEASE_NULL(pRet);
      return NULL;
  }
    
    
    
    return s_musicPlayer;
}


MusicPlayer::MusicPlayer()
{
    

}



MusicPlayer::~MusicPlayer()
{
    end();
}


bool MusicPlayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!Node::init());
         m_player = SimpleAudioEngine::getInstance();
        CC_BREAK_IF(!m_player);
        
         _running = true;
         onEnter();
        if (_isTransitionFinished)
        {
          onEnterTransitionDidFinish();
        }
        
        bRet = true;
    } while (0);


    return bRet;
}



void MusicPlayer::end()
{
    MusicMap::iterator mapIter;
    for (mapIter = m_musicMap.begin(); mapIter != m_musicMap.end(); )
    {
        mapIter->second->release();
        m_musicMap.erase(mapIter++);
    }
  
    m_musicMap.clear();
}






void MusicPlayer::preloadEffect(int ID)
{
    do {
        
        MusicMap::iterator it = m_musicMap.find(ID);
        CC_BREAK_IF(it != m_musicMap.end());//已经存在

        MusicInfo* info = MusicInfo::create(ID); 
        CC_BREAK_IF(!info);
        info->retain();
        
        m_musicMap.insert(MusicMap::value_type(ID,info));
        m_player->preloadEffect(info->getPath().c_str());
                
    } while (0);

}

void MusicPlayer::playEffect(int ID)
{
    MusicMap::iterator it = m_musicMap.find(ID);
    if(it == m_musicMap.end())
        return;
    
    MusicInfo* info = it->second;
    float delay = info->getDelay();
    FiniteTimeAction* sq = Sequence::create(DelayTime::create(delay),CallFunc::create(CC_CALLBACK_0(MusicPlayer::play, this, info)), NULL);
    this->runAction(sq);

}





void MusicPlayer::play(MusicInfo* info)
{
    if(info == NULL)
        return;
        
    unsigned int id = (unsigned int)m_player->playEffect(info->getPath().c_str(),true);
    
    Integer* musicId = Integer::create(id);
    musicId->retain();
    float lifeTime = info->getLifeTime();
    FiniteTimeAction* sq = Sequence::create(DelayTime::create(lifeTime),CallFunc::create(CC_CALLBACK_0(MusicPlayer::stopByMusicId, this, musicId)), NULL);
    this->runAction(sq);
    
   // log("%s %f %f %d",info->getPath().c_str(), info->getDelay(), info->getLifeTime(),musicId->getValue());
 
}


void  MusicPlayer::stopByMusicId(Integer* musicId)
{
    unsigned int id = (unsigned int)musicId->getValue();
    m_player->stopEffect(id);
    musicId->release();
    //log("stop %d",id);

}














