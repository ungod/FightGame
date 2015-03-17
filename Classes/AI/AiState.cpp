#include "AiState.h"
#include "Utils/StringUtils.h"
#include "Utils/MathUtils.h"

AiState::AiState()
{
	m_aiModule = NULL;
	m_aiAction = NULL;
}

AiState::~AiState()
{
}

void AiState::init( SqliteResolver* sr, AiModule* module)
{
	m_elapse = 0;
	m_aiModule = module;
	m_maxCoolDown = m_coolDown = 0;
	m_state = kAiPolling;

	parse(sr);
}

void AiState::parse( SqliteResolver* sr )
{
	string condition = sr->getString("Condition");
	string action = sr->getString("Action");
	string next = sr->getString("Next");

	m_id = sr->getInt("AIID");
	m_actionOdds = sr->getFloat("Odds");
	m_maxCoolDown = sr->getFloat("CoolDown");

	sr->release();

	vector<string> conArr;
	splitString(condition, "|", conArr);

	vector<string>::iterator it;
	AiCondition* aicond;
	for (it = conArr.begin(); it != conArr.end(); it++)
	{
		aicond = new AiCondition(m_aiModule, *it);
		m_aiConditions.push_back(aicond);
	}

	vector<string> nextArr;
	splitStringWithForm(next, nextArr);

	for (it = nextArr.begin(); it != nextArr.end(); it++)
	{
		m_nextStates.push_back(atoi((*it).c_str()));
	}

	m_aiAction = new AiAction(m_aiModule, action);
	m_coolDown = 0;
}


bool AiState::poll( float dt )
{
	m_elapse += dt;
	m_coolDown -= dt;
	vector<AiCondition*>::iterator it;
	for (it = m_aiConditions.begin(); it != m_aiConditions.end(); it++)
	{
		if ((*it)->isTrue() && m_coolDown <= 0 && m_elapse >= m_aiAction->getDelay() && 
			m_aiAction && oddsHit(m_actionOdds))
		{
			m_aiAction->doAction();
			m_elapse = 0;
			m_coolDown = m_maxCoolDown;
			m_state = kAiIdling;
			return true;
		}
	}
	return false;
}

bool AiState::idle( float dt )
{
	m_elapse += dt;

	if (m_elapse >= m_aiAction->getIdle())
	{
		m_elapse = 0;
		m_state = kAiFinish;
		return true;
	}
	return false;
}

int AiState::next()
{
	if (m_nextStates.size() <= 0)
		return -1;

	m_state = kAiPolling;

	return m_nextStates[rand()%m_nextStates.size()];
}

