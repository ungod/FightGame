#pragma once

#include "BaseFrame/CKBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;


class PropertyLoader : public Object
{
public:
    static PropertyLoader* create(const char* plistFile);
    bool init(const char* plistFile);
    PropertyLoader();
    virtual ~PropertyLoader() ;
 
    bool initWithDictionary(Dictionary *dictionary);//从dictionary初始化
    bool initWithDictionary(Dictionary *dictionary, const char *dirname);
    
protected:
    std::string m_sPlistFile;
} ;


