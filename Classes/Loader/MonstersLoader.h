#pragma once
#include "cocos2d.h"
#include "Loader.h"
#include "MonstersLoaderData.h"
USING_NS_CC;
using namespace std;

#define MONSTERS_GROUP_COUNT 6//怪物最大组数




//怪物加载器
class MonstersLoader :public Loader
{
public:
    static MonstersLoader* create(int ID);
    bool initWithID(int ID);
    
    MonstersLoader();
    ~MonstersLoader();
    
    Array* getGroupAt(int index);
    Array* getMonstersGroup();//选择期中一组
    
    //@brief 怪物组数
    CC_SYNTHESIZE(int, m_groupCount, GroupCount);
    
    //@brief 当前使用的怪物组
    CC_SYNTHESIZE(int, m_groupIndex, GroupIndex);
    
    
    //@brief 保存怪物组的列表
    CC_SYNTHESIZE(Array*, m_monstersArray, MonstersArray);

};
