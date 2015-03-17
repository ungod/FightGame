#pragma once
#include "cocos2d.h"

#include <vector>
#include "AiAction.h"
#include "AiCondition.h"

USING_NS_CC;
using namespace std;

enum AiStatesRunningStates
{
	kAiPolling = 0,
	kAiIdling,
	kAiFinish
};

class AiAction;
class AiCondition;

class AiState
{
public:
	AiState();
	~AiState();

	void init(SqliteResolver* sr, AiModule* module);
	void parse(SqliteResolver* sr);

	bool poll(float dt);
	bool idle(float dt);
	int next();

	CC_SYNTHESIZE(AiStatesRunningStates, m_state, State);
	CC_SYNTHESIZE(int, m_id, ID);

private:
	AiModule* m_aiModule;

	vector<AiCondition*>	m_aiConditions;
	vector<int>				m_nextStates;
	AiAction*				m_aiAction;

	float m_actionOdds;
	float m_coolDown;
	float m_maxCoolDown;
	float m_elapse;
};
