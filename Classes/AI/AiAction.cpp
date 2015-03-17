#include "AiAction.h"
#include "Utils/StringUtils.h"


USING_NS_CC;

AiAction::AiAction( AiModule* module, const string& params )
{
	m_aiModule = module;

	vector<string> strArr;
	splitStringWithForm(params, strArr);

	vector<string>::iterator it;
	for (it = strArr.begin(); it != strArr.end(); it++)
	{
		if (it == strArr.begin())
		{
			m_actionID = atoi((*it).c_str());
		}
		else if (it == strArr.begin() + 1)
		{
			m_delay = atof((*it).c_str());
		}
		else if (it == strArr.begin() + 2)
		{
			m_idle = atof((*it).c_str());
		}
		else
		{
			m_param.push_back(atoi((*it).c_str()));
		}
	}
}

AiAction::~AiAction()
{
	m_aiModule = NULL;
}

void AiAction::doAction()
{
	switch (m_actionID)
	{
	case 0:
		action0();
		break;
	case 1:
		action1();
		break;
	case 2:
		action2();
		break;
	case 3:
		action3();
		break;
	default:
		break;
	}
}

void AiAction::action0()
{
	m_aiModule->getHost()->attack();
}

void AiAction::action1()
{
	if (m_param[0] == 0)
	{
		m_aiModule->getHost()->walkWithDirection(Point(m_param[1], m_param[2]), m_param[3]);
	}
	else
	{
		m_aiModule->getHost()->walkWithTarget(Point(m_param[1], m_param[2]));
	}
}

void AiAction::action2()
{
	m_aiModule->getHost()->runSkillWithIndex(m_param[0]);
}

void AiAction::action3()
{

}