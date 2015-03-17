#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class MusicInfo : public Object
{
public:
    MusicInfo();
    ~MusicInfo();
    static MusicInfo* create(int ID);
    bool initWithID(int ID);
    
    
    
    CC_SYNTHESIZE(string, m_path, Path);
    CC_SYNTHESIZE(float, m_delay, Delay);
    CC_SYNTHESIZE(float, m_lifeTime, LifeTime);
          

};
