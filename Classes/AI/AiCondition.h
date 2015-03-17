#pragma once
#include "cocos2d.h"
#include "Sprites/AnimationSprite.h"
#include "AiModule.h"

USING_NS_CC;

#define CONDITION_FUNC(id) bool condition##id(...)

class AiModule;

class AiCondition
{
public:
	AiCondition(AiModule* module, const string& params);
	~AiCondition(void);

	bool isTrue();

private:
	bool condition0();
	bool condition1();
	bool condition2();
	bool condition3();

private:
	AiModule*	m_aiModule;
	vector<int> m_param;
	int			m_conditionID;
};
