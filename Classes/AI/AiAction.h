#pragma once
#include "cocos2d.h"
#include "AiModule.h"

USING_NS_CC;
using namespace std;

class AiModule;

class AiAction
{
public:
	AiAction(AiModule* module, const string& params);
	~AiAction();

	void doAction();

private:
	void action0();
	void action1();
	void action2();
	void action3();

	CC_SYNTHESIZE_READONLY(float, m_delay, Delay);
	CC_SYNTHESIZE_READONLY(float, m_idle, Idle);

private:
	AiModule*	m_aiModule;
	vector<int> m_param;
	int			m_actionID;
};
