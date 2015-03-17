
#include "PropertyLoader.h"


PropertyLoader* PropertyLoader::create(const char* plistFile)
{
    PropertyLoader* pLoader = new PropertyLoader();
    if(pLoader && pLoader->init(plistFile))
    {
        pLoader->autorelease();
        return pLoader;
    }
    
    CC_SAFE_RELEASE(pLoader);
    pLoader = NULL;
    return NULL;
}

PropertyLoader::PropertyLoader()
{
  
}
PropertyLoader::~PropertyLoader() 
{
    
}


bool PropertyLoader::init(const char* plistFile)
{
    bool bRet = false;
    
    do {
        m_sPlistFile = CCFileUtils::getInstance()->fullPathForFilename(plistFile);
        Dictionary* dict = Dictionary::createWithContentsOfFileThreadSafe(m_sPlistFile.c_str());
        CCAssert(dict != NULL, "Info file not found");
        
        string listFilePath = plistFile;
        if(listFilePath.find('/') != string::npos)
        {
            listFilePath = listFilePath.substr(0, listFilePath.find('/') + 1);
            bRet = this->initWithDictionary(dict, listFilePath.c_str());
        }
        
        else
        {
            bRet = this->initWithDictionary(dict, "");
        }
        
        
        
        bRet = true;
    } while (0);
    
    
    
    return bRet;
}


bool PropertyLoader::initWithDictionary(Dictionary *dictionary)
{
    return initWithDictionary(dictionary, "");
}

/*
 <key>pos</key>
 <string>{360, 100}</string>
 
 CCPoint: CCPointFromString(); {x, y}
 CCSize:  CCSizeFromString(); {w, h}
 CCRect: CCSizeFromString(); {{x,y},{w,h}}
 
 
 
 
 */

bool PropertyLoader::initWithDictionary(Dictionary *dictionary, const char *dirname)
{
    bool bRet = false;
 
    do
    {
        
        //ParticleSystem
        //SpriteFrameCache
        //int maxParticles = dictionary->valueForKey("maxParticles")->intValue();
//        DictElement* element = NULL;
//        CCDICT_FOREACH(dictionary, element)
//        {
//            log("%s--->%s",element->getStrKey(),static_cast<String*>(element->getObject())->getCString() );
//            //element->
//        }
        
        string m_skillName = dictionary->valueForKey("SkillName")->getCString();
        log("m_skillName:%s",m_skillName.c_str());
        
        string m_skillIcon = dictionary->valueForKey("SkillIcon")->getCString();
        log("SkillIcon:%s",m_skillIcon.c_str());
        
        string m_skillIconDisabled = dictionary->valueForKey("SkillIconDisabled")->getCString();
        log("SkillIconDisabled:%s",m_skillIconDisabled.c_str());

        
        string m_skillMusic = dictionary->valueForKey("SkillMusic")->getCString();
        log("SkillMusic:%s",m_skillMusic.c_str());
        
        float m_skillMPConsume = dictionary->valueForKey("SkillMPConsume")->floatValue();
        float m_skillCD = dictionary->valueForKey("SkillCD")->floatValue();
        float m_skillHitJudgement = dictionary->valueForKey("SkillHitJudgement")->floatValue();
        log("SkillMPConsume:%f SkillCD:%f SkillHitJudgement:%f",m_skillMPConsume,m_skillCD,m_skillHitJudgement);
        
        float m_skillCondition = dictionary->valueForKey("SkillCondition")->floatValue();
        float m_skillPlace = dictionary->valueForKey("SkillPlace")->floatValue();
        log("SkillCondition:%f SkillPlace:%f",m_skillCondition,m_skillPlace);

        
        
        Point m_aiDistance = PointFromString(dictionary->valueForKey("AiDistance")->getCString());
        log("m_aiDistance x:%f z:%f",m_aiDistance.x, m_aiDistance.y );

        Array* m_skillActionArray = (Array*)dictionary->objectForKey("SkillAction");
        Object* obj = NULL;
        CCARRAY_FOREACH(m_skillActionArray, obj)
        {
            String* actionPlist = (String*)obj;
            log("skillActionDict %s",actionPlist->getCString() );
        }
        
        
        Dictionary* skillActionDict = (Dictionary*)dictionary->objectForKey("SkillLight");
        DictElement* element = NULL;
        CCDICT_FOREACH(skillActionDict, element)
        {
            Dictionary* skillLight = static_cast<Dictionary*>(element->getObject());
            string eleName = element->getStrKey();
            string xy = skillLight->valueForKey("AppearCoordinate")->getCString();
            string fileName = skillLight->valueForKey("FileName")->getCString();

            log("%s: xy:%s fileName:%s",eleName.c_str(),xy.c_str(),(dirname +fileName).c_str());
        }
        
      
//        Rect rect = RectFromString(dictionary->valueForKey("rect")->getCString());
//        log("x:%f y:%f w:%f h:%f  %s",rect.origin.x, rect.origin.y ,rect.size.width, rect.size.height, dirname);

        
        bRet = true;
        
    } while (0);
  
    return bRet;
}


