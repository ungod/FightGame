#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class MusicInterface
{
public:
    MusicInterface();
    ~MusicInterface();
    
    //@brief 音效的gl ID
    CC_SYNTHESIZE(unsigned int, m_glID, GlID);
          

};
