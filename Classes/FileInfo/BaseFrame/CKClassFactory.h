

#ifndef Blog_C___Reflection_CKClassFactory_h
#define Blog_C___Reflection_CKClassFactory_h

#include<string>
#include<map>
#include<iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std ;

typedef void* (*createClass)(void) ;

class CKClassFactory 
{
public:
    CKClassFactory() ;
    
    virtual ~CKClassFactory() ;
    
    void* getClassByName(string className) ;
    
    void registClass(string name, createClass method) ;
    
    static CKClassFactory& getInstance() ;
    
private:
    map<string, createClass> m_classMap ;
} ;


#endif
