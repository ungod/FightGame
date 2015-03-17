

#ifndef Blog_C___Reflection_CKBaseClass_h
#define Blog_C___Reflection_CKBaseClass_h

#include "CKDynamicClass.h" 
#include "cocos2d.h"
USING_NS_CC;

class CKBaseClass ;

typedef void (*setValue)(CKBaseClass *t, void* c) ;

class CKBaseClass
{
private:
    DECLARE_CLASS(CKBaseClass)
    
public:
    CKBaseClass() ;
    virtual ~CKBaseClass();
    static void* createInstance() ;
    virtual void registProperty() ;
    virtual void display() ;
    map<string, setValue> m_propertyMap ;
} ;


#define CK_MEMBER(varName) m_##varName  //获取成员变量名称

#define SYNTHESIZE(classType, varType, varName)    \
public:                                             \
inline static void set##varName(CKBaseClass*cp, void*value){ \
    classType* tp = (classType*)cp ;                        \
    tp->CK_MEMBER(varName) = (varType)value ;                      \
}                                                       \
inline varType get##varName(void) const {                \
    return CK_MEMBER(varName) ;                                      \
}  \
protected:                        \
  varType CK_MEMBER(varName) ;      



#define REG_VALUE(funcName, varName)    \
 m_propertyMap.insert(pair<string, setValue>(funcName, set##varName))  //注册函数名称



#endif
