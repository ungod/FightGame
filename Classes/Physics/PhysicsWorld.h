#pragma once
#include "cocos2d.h"
#include "MyContactListener.h"
#include "CCArmature/external_tool/GLES-Render.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

USING_NS_CC;

#include <list>
using std::list;



struct b2Manifold;
struct b2ContactImpulse;
class b2Fixture;
class b2Contact;
class b2World;


class MyContactListener;


class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld();
    static PhysicsWorld *create();
    bool initWorld();
    CC_SYNTHESIZE(b2Body*, m_groundBody, GroundBody);

private:    
    b2World *m_pWorld;    
    MyContactListener *m_pContactListener;//碰撞监听
    extension::armature::GLESDebugDraw *m_pDebugDraw;  //调试绘画
 
public:
    void update(float dt);
    void drawDebug();
    b2World *getWorld();

};

