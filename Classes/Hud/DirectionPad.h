#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DirectionPad;

class DirectionPadDelegate
{
public:
	virtual void onDirectionChanged(Point direction) = 0;
	virtual void onKeepDirection(Point direction) = 0;
	virtual void onDirectionEnded() = 0;
};

class DirectionPad : public Sprite, public TouchDelegate
{
public:
	DirectionPad(void);
	~DirectionPad(void);

	static DirectionPad* create(String *fileName, float radius);//创建方向盘
	bool initWithFile(String *fileName, float radius);

	void onEnterTransitionDidFinish();
	void onExit();
	void update(float dt);

	virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);

	void updateDirectionForTouchLocation(Point location);
    void setCirclePosition(Point location);

	CC_SYNTHESIZE(DirectionPadDelegate*, m_delegate, Delegate);
	CC_SYNTHESIZE(bool, m_isHeld, IsHeld);

protected:
	float m_radius;
	Point m_direction;
    SpriteBatchNode* m_DPad;
    Sprite* m_circle;
};
