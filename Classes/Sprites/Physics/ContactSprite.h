#pragma once

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "BasePhysicsSprite.h"
#include "ContactAnimateSprite.h"
#include "Geometries/Point3D.h"
#include "HitBox/HitBox.h"
#include "../AnimateBase/Animate3D.h"
USING_NS_CC;

class b2Body;

/****
* 用来检测碰撞的单体精灵类
* 
*0
**/

class ContactSprite : public BasePhysicsSprite, public Animate3D, public HitBox
{
public:
    ContactSprite();
	~ContactSprite();

	virtual bool init();
    virtual bool initWithHitBoxID(int ID);

    void initBody();//初始化b2Body;
    void updateFixture();//刷新fixture
    void removeFromParentAndCleanup(bool cleanup) override;
    
    virtual void setX(float x) override;//x坐标
    virtual void setY(float y) override;//y坐标
    virtual void setZ(float z) override;//z坐标
    
    //重载设置位置
    virtual void setPosition(const Point &position);
    virtual void updatePosition(const Point &position);
    
    //@brief 启动的时候进行回调
    virtual void onStarted();
    
    //@brief 结束的时候进行回调
    virtual void onFinished();
    
    //更新下次有效的碰撞时间
    void updateCollideTime();
    //检测时候可以进行碰撞,依据碰撞频率来决定的
    //@param autoUpdate 是否自动更新下次的决定时间
    virtual bool canCollide(bool autoUpdate = true);

	virtual bool checkCollision(AnimationSprite* pTarget);
    
    //与角色发生碰撞
    virtual void onCollsion(AnimationSprite* pTarget);

    //有效碰撞的判断时间
    CC_SYNTHESIZE(double, m_nextCollideTime, NextCollideTime);
    
	//显示对象
	CC_SYNTHESIZE(AnimationSprite*, m_owner, Owner);

public:
	bool m_bIsBullet;

protected:
	uint16 m_categoryBits;
	uint16 m_maskBits;

private:
	bool m_bIsFinish;
	b2World* m_world;
};




