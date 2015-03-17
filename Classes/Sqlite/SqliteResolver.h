#pragma once
#include "cocos2d.h"
#include "sqlite3.h"
#include "SqliteHelper.h"
#include "Geometries/Point3D.h"
#include "Sprites/Decoration/ShadowSprite.h"
#include "Sprites/BaseSprites/SimpleAnimation.h"

USING_NS_CC;
using namespace std;

class SqliteResolver : public Object
{

public:
	SqliteResolver();
    ~SqliteResolver();
    static SqliteResolver* create(SqliteTable* table);
    static SqliteResolver* create(const char* szSQL);
    static SqliteResolver* create(const char* tableName, int ID);
    
    bool init(const char* szSQL);
    bool init(SqliteTable* table);
    bool init(const char* tableName, int ID);
    
    static bool loadSimpleSprite(const char* path, const char* animationName, int pngNum);
    char* loadSimpleSprite();//加载动画,成功返回动画名称
    SimpleAnimation* getSimpleSprite();
    //static ShadowSprite* getShadowSprite(const char* stringName);

	int getRow();
	void setRow(int row);
    
    Array* getArray(const char* arrayName);
    Array* getIntArray(const char* arrayName);
    Point  getPoint(const char* pointName);
    Size   getSize(const char* sizeName);
    Rect   getRect(const char* rectName);    
    int    getInt(const char* intName);
    float  getFloat(const char* floatName);
    string getString(const char* stringName);
    
    Point3D getPoint3D(const char* pointName, float xScale = 1.0f);
    Sequence* getPoint3DSequance(const char* actionName, float xScale = 1.0f);
    static Sequence* SequenceWithCallback(Sequence* sequance, CallFunc* callFunc);    
    
    
    CC_SYNTHESIZE_RETAIN(SqliteTable*, m_table, Table);
    
    
    
};
