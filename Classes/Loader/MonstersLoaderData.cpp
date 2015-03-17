#include "MonstersLoaderData.h"
#include "Geometries/Point3D.h"



MonstersLoaderData::MonstersLoaderData()
{
    m_ID = 0;
}



MonstersLoaderData::~MonstersLoaderData()
{
    

}



MonstersLoaderData* MonstersLoaderData::create(const char* dataString)
{
    MonstersLoaderData* pRet = new MonstersLoaderData();
    if(pRet && pRet->initWithString(dataString))
    {
        pRet->autorelease();
        return pRet;
    
    }
    
    CC_SAFE_RELEASE(pRet);
    return NULL;
    
}





bool MonstersLoaderData::initWithString(const char* dataString)
{
    if( dataString == NULL)
        return false;
    
    Point3D point = Point3DFromString(dataString);
    
    //dataString 中包含{x,z,id}信息
    m_position = Point3D(point.x, 0, point.y);
   
    m_ID = (int)point.z;
    
    
    return true;
}




