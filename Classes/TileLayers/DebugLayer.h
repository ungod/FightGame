#pragma once
#include "cocos2d.h"
USING_NS_CC;


class DebugLayer : public Node
{
public:
    DebugLayer();
    ~DebugLayer();

    
    static DebugLayer* create();
    bool init();
    virtual void draw();

};
