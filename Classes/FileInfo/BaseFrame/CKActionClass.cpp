
#include "CKActionClass.h"

IMPLEMENT_CLASS(CKActionClass)
CKActionClass::CKActionClass()
{
  registProperty();
}
CKActionClass::~CKActionClass() 
{
    
}
void* CKActionClass::createInstance()
{
    return new CKActionClass() ;
}
void CKActionClass::registProperty() 
{
    //m_propertyMap.insert(pair<string, setValue>("setpValue", setpValue)) ;
    REG_VALUE("setpValue", pValue);

}
void CKActionClass::display()
{
    log("%d",*getpValue()) ;
}
