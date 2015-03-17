

#include "CKDynamicClass.h"

CKDynamicClass::CKDynamicClass(string name, createClass method) 
{
    CKClassFactory::getInstance().registClass(name, method) ;
}