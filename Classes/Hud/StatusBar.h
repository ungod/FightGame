#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DataInfo/RoleProperty.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StatusBar : public Sprite
{
public:
	StatusBar();
	~StatusBar();

	static StatusBar* create(AnimationSprite* owner);

	bool init(AnimationSprite* owner);

	virtual void setOpacity(GLubyte opacity);
	virtual void onCurrentHPChange(RoleProperty* prop);

private:
	Sprite* m_pHead;
	LabelTTF* m_pLevel;
	AnimationSprite* m_pOwner;
	ProgressTimer* m_pBloodBar;
	ProgressTimer* m_pManaBar;
};