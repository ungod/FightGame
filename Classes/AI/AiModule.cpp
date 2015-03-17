#include "AiModule.h"
#include "Utils/MiscUtils.h"


USING_NS_CC;

#define SCOUT_RANGE FLT_MAX
#define ALERT_RANGE 150
#define OFFSET 50

AiModule::AiModule()
{
	m_host = NULL;
	m_target = NULL;

	m_sqlRsl = NULL;

	m_currentStateIndex = 0;
	m_bQuaterNotSlant = false;
	m_targetOwnTime = 0;
	m_states = kScoutStates;
}

AiModule::~AiModule()
{
	m_host = NULL;
	m_target = NULL;

	CC_SAFE_RELEASE_NULL(m_sqlRsl);
	DELETE_VECTOR_PTR(vector<AiState*>, m_aiStates)
}

bool AiModule::init( int moduleID, AnimationSprite* host)
{
	String* sql = String::createWithFormat("SELECT * FROM %s WHERE AiModule=%d ;",TABLE_AI_STATES, moduleID);
	SqliteTable* table = SqliteHelper::getInstance()->getTable(sql->getCString());

	if (!table)
		return false;

	m_sqlRsl = SqliteResolver::create(table);

	if (!m_sqlRsl)
		return false;

	m_sqlRsl->retain();

	m_host = host;
	m_host->retain();

	m_currentStateIndex = 0;
	m_bQuaterNotSlant = rand() % 2  == 1;
	m_bPathParal = rand() % 2 == 1;

	parse();

	return true;
}

void AiModule::parse()
{
	AiState* state;
	int row = m_sqlRsl->getRow();

	for (int i=0; i<row; i++)
	{
		state = new AiState;
		m_sqlRsl->setRow(i);
		state->init(m_sqlRsl, this);
		m_aiStates.push_back(state);
	}
	sort(m_aiStates.begin(), m_aiStates.end(), stateSort);
}

void AiModule::tick(float dt, Array* targetArray, Array* roleArray)
{
	if (m_currentStateIndex < 0 || m_currentStateIndex >= m_aiStates.size())
		return;

	m_targetArray = targetArray;
	m_roleArray = roleArray;

	switch (m_states)
	{
	case kScoutStates:
		{
			Object* obj;
			CCARRAY_FOREACH(targetArray, obj)
			{
				AnimationSprite* sprite = (AnimationSprite*)obj;
				Point vec = sprite->getCenterPosition() - m_host->getCenterPosition();

				if(vec.getLength() < SCOUT_RANGE)
				{
					m_target = sprite;
					m_target->retain();
					m_states = kAlertStates;
					break;
				}
			}
		}
		break;
	case kAlertStates:
		{
			Point vec = m_target->getCenterPosition() - m_host->getCenterPosition();
			m_host->setFaceDirection(vec);

			if (vec.getLength() < ALERT_RANGE)
			{
				m_states = kChaseStates;
			}
		}
		break;
	case kChaseStates:
		{
			if (m_target->getActionState() != kActionStateKnockedOut)
			{
				m_host->setFaceDirection(m_target->getCenterPosition() - m_host->getCenterPosition());
				m_targetOwnTime += dt;

				AiState* state = m_aiStates[m_currentStateIndex];
				switch (state->getState())
				{
				case kAiPolling:
					chase();
					state->poll(dt);
					break;
				case kAiIdling:
					state->idle(dt);
					break;
				case kAiFinish:
					m_currentStateIndex = state->next();
					break;
				}
			}
			else
			{
				CC_SAFE_RELEASE_NULL(m_target);
				m_states = kScoutStates;
			}
		}
		break;
	default:
		break;
	}
}

void AiModule::chase()
{
	//追逐方式，可重载
	m_bQuaterNotSlant ? quaterFinding() : slantFinding();
}

void AiModule::quaterFinding()
{
	//直角寻路
	Point vec = m_target->getCenterPosition() - m_host->getCenterPosition();
	Point step1, step2;

	step1 = step2 = vec;

	if (m_bPathParal)
	{
		step1.y = 0;
		step2.x = 0;
	}
	else
	{
		step1.x = 0;
		step2.y = 0;
	}

	if (step1.getLength() >= OFFSET)
	{
		m_host->walkWithDirection(step1.normalize(), 0, false);
	}
	else if (step2.getLength() >= OFFSET)
	{
		m_host->walkWithDirection(step2.normalize(), 0, false);
	}
}

void AiModule::slantFinding()
{
	//斜线寻路
	int mulx = rand()%2 ? -1 : 1;
	int muly = rand()%2 ? -1 : 1;

	Point offset(mulx*rand()%OFFSET, muly*rand()%OFFSET);
	m_host->walkWithTarget(m_target->getCenterPosition() + offset, false);
}

bool AiModule::stateSort( const AiState* ai1, const AiState* ai2 )
{
	return ai1->getID() < ai2->getID();
}