

#include "CKClassFactory.h"

CKClassFactory::CKClassFactory() 
{
}

CKClassFactory::~CKClassFactory() 
{
}

void* CKClassFactory::getClassByName(string className) 
{
    map<string, createClass>::const_iterator iter ;
    
    iter = m_classMap.find(className) ; 
    if ( iter == m_classMap.end() )
        return NULL ;
    else 
        return iter->second() ;
}

void CKClassFactory::registClass(string name, createClass method) 
{
    m_classMap.insert(pair<string, createClass>(name, method)) ;
}

CKClassFactory& CKClassFactory::getInstance() 
{
    static CKClassFactory instance ;
    return instance ;
}