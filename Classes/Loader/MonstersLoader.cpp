#include "Loader/MonstersLoader.h"
#include "Sqlite/SqliteResolver.h"




MonstersLoader::MonstersLoader()
{
    m_groupCount = 0;
    m_groupIndex = 0;
    m_monstersArray = NULL;

}



MonstersLoader::~MonstersLoader()
{
   CC_SAFE_RELEASE(m_monstersArray);
}



MonstersLoader* MonstersLoader::create(int ID)
{
    MonstersLoader* pRet = new MonstersLoader();
    if(pRet && pRet->initWithID(ID))
    {
        pRet->autorelease();
        return  pRet;
    }
    
    CC_SAFE_RELEASE(pRet);
    return NULL;

}



bool MonstersLoader::initWithID(int ID)
{
    bool bRet = false;
    do {
        SqliteResolver* resolver = SqliteResolver::create(TABLE_MONSTERS_LOADER, ID);
        CC_BREAK_IF(!resolver);
        
        m_monstersArray = Array::create();
        CC_BREAK_IF(!m_monstersArray);
        m_monstersArray->retain();
        
        int count = 0;
        for(int i = 0; i < MONSTERS_GROUP_COUNT; i++)//计算真实的组数
        {
            String* groupHeaderText = String::createWithFormat("Group%d",i);
            string str = resolver->getString(groupHeaderText->getCString());
            if(str.length() <= 0)
            {
                break;
            }
            
            Array* groupArray = resolver->getArray(groupHeaderText->getCString());//单组
            Array* groupData = Array::create();
            for( int j = 0; j < groupArray->count(); j++)
            {
                String* dataString = (String*)groupArray->objectAtIndex(j);
                MonstersLoaderData* pData = MonstersLoaderData::create(dataString->getCString());
                
                CCAssert(pData != NULL,"MonsterData is NULL");
                if(pData == NULL)
                    return false;
                
                groupData->addObject(pData);
                
            }
            
            m_monstersArray->addObject(groupData);
            count++;
        }
        
        setGroupCount(count);
        
       
       
        bRet = true;
    } while (0);

    return  bRet;
}



Array* MonstersLoader::getGroupAt(int index)
{
  if(index < m_groupCount && index >= 0)
      return (Array*)m_monstersArray->objectAtIndex(index);
    
    else
        return NULL;

}


Array* MonstersLoader::getMonstersGroup()
{
    if (m_groupIndex < m_groupCount)
    {
        int retIndex = m_groupIndex;
        m_groupIndex++;
        
        return getGroupAt(retIndex);
    }
    
    return NULL;
}






