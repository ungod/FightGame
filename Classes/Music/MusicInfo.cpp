#include "MusicInfo.h"
#include "Sqlite/SqliteResolver.h"

MusicInfo* MusicInfo::create(int ID)
{
    MusicInfo* pRet = new MusicInfo();
    
    if( pRet && pRet->initWithID(ID))
    {
        return pRet;
    
    }
    
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;
}


MusicInfo::MusicInfo()
{
    m_path = "";
    m_delay = 0;
    m_lifeTime = 0;

}



MusicInfo::~MusicInfo()
{
    

}


bool MusicInfo::initWithID(int ID)
{
    bool bRet = false;
    
    do {
        SqliteResolver* resolver = SqliteResolver::create(TABLE_MUSIC, ID);
        CC_BREAK_IF(!resolver);
        
        m_path = resolver->getString("Path");
        m_delay = resolver->getFloat("Delay");
        m_lifeTime = resolver->getFloat("LifeTime");
        
        //log("%s %f %d",m_path.c_str(), m_delay, m_loop);
        
        bRet = true;
    } while (0);


    return bRet;
}




