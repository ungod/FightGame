#pragma once
#include "cocos2d.h"
#include "Geometries/Point3D.h"
USING_NS_CC;
using namespace std;


class MonstersLoaderData : public Object
{
public:
    
    static MonstersLoaderData* create(const char* dataString);
    bool initWithString(const char* dataString);
    
    
    MonstersLoaderData();
    ~MonstersLoaderData();
    

    CC_SYNTHESIZE(Point3D, m_position, Position);
    CC_SYNTHESIZE(int, m_ID, ID);//怪物id
    

};
