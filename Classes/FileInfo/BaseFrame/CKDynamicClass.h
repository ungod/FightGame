

#ifndef Blog_C___Reflection_CKDynamicClass_h
#define Blog_C___Reflection_CKDynamicClass_h

#include"CKClassFactory.h"
#include "cocos2d.h"

USING_NS_CC;


class CKDynamicClass 
{
public:
    CKDynamicClass(string name, createClass method) ;
} ;

#define DECLARE_CLASS(className)\
string className##Name ;        \
static CKDynamicClass* m_className##dc ;

#define IMPLEMENT_CLASS(className)  \
CKDynamicClass* className::m_className##dc = \
new CKDynamicClass(#className, className::createInstance) ;



#endif
