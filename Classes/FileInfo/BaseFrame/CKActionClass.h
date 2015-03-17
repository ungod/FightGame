
#ifndef Blog_C___Reflection_CKHelloClass_h
#define Blog_C___Reflection_CKHelloClass_h


#include "CKBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;


class CKActionClass : public CKBaseClass
{
private:
    DECLARE_CLASS(CKActionClass)
    
public:
    CKActionClass() ;
    virtual ~CKActionClass() ;
    static void* createInstance() ;
    virtual void registProperty() ;
    virtual void display() ;
    
    SYNTHESIZE(CKActionClass, int*, pValue);
    SYNTHESIZE(CKActionClass, ScaleBy*, ScaleBy);
} ;

#endif
