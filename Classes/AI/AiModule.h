#pragma once
#include "cocos2d.h"
#include "AiState.h"
#include "Sprites/AnimationSprite.h"

USING_NS_CC;

enum AiModuleStates
{
	kScoutStates = 0,
	kAlertStates,
	kChaseStates
};


class AiState;

class AiModule
{
public:
	AiModule();
	~AiModule();
	
	bool init(int moduleID, AnimationSprite* host);

	virtual void parse();
    virtual void tick(float dt, Array* targetArray, Array* roleArray);

	virtual void chase();

	void quaterFinding();
	void slantFinding();

	static bool stateSort(const AiState* ai1, const AiState* ai2);

	CC_SYNTHESIZE_READONLY(AnimationSprite*, m_host, Host);
	CC_SYNTHESIZE_READONLY(AnimationSprite*, m_target, Target);
	CC_SYNTHESIZE_READONLY(float, m_targetOwnTime, TargetOwnTime);
	CC_SYNTHESIZE_READONLY(Array*, m_roleArray, RoleArray);
	CC_SYNTHESIZE_READONLY(Array*, m_targetArray, TargetArray);

private:
	vector<AiState*> m_aiStates;
	SqliteResolver* m_sqlRsl;

	unsigned int m_currentStateIndex;
	bool m_bQuaterNotSlant;
	bool m_bPathParal;

	AiModuleStates m_states;
};
