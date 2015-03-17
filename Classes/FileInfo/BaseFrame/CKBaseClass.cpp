

#include <iostream>

#include "CKBaseClass.h"

IMPLEMENT_CLASS(CKBaseClass)

CKBaseClass::CKBaseClass() 
{
  
}
CKBaseClass::~CKBaseClass() 
{
    
}
void* CKBaseClass::createInstance() 
{
    return new CKBaseClass() ;
}
void CKBaseClass::registProperty() 
{
    //overwrite method at subclass
}
void CKBaseClass::display() 
{
    
}