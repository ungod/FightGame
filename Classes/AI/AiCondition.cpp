#include "AiCondition.h"
#include "Utils/StringUtils.h"

USING_NS_CC;

AiCondition::AiCondition( AiModule* module, const string& params )
{
	m_aiModule = module;
	m_conditionID = 0;

	vector<string> strArr;
	splitStringWithForm(params, strArr);

	vector<string>::iterator it;
	for (it = strArr.begin(); it != strArr.end(); it++)
	{
		if (it == strArr.begin())
		{
			m_conditionID = atoi((*it).c_str());
		}
		else
		{
			m_param.push_back(atoi((*it).c_str()));
		}
	}
}

AiCondition::~AiCondition()
{
	m_aiModule = NULL;
}

bool AiCondition::isTrue()
{
	bool result = false;

	switch (m_conditionID)
	{
	case 0:
		result = condition0();
		break;
	case 1:
		result = condition1();
		break;
	case 2:
		result = condition2();
		break;
	case 3:
		result = condition3();
		break;
	default:
		break;
	}

	return result;
}

bool AiCondition::condition0()
{
	Point p = m_aiModule->getTarget()->getCenterPosition() - m_aiModule->getHost()->getCenterPosition();
	int len = p.getLength();
	bool result = false;

	switch (m_param[0])
	{
	case 0:
		result = len < m_param[1];
		break;
	case 1:
		result = len == m_param[1];
		break;
	case 2:
		result = len > m_param[1];
		break;
	}

	return result;
}

bool AiCondition::condition1()
{
	RoleProperty* prop = m_aiModule->getHost()->getRoleProperty();
	int hpPercent = (prop->getCurrentHP() / prop->getMaxHP())*100;
	bool result = false;

	switch (m_param[0])
	{
	case 0:
		result = hpPercent < m_param[1];
		break;
	case 1:
		result = hpPercent == m_param[1];
		break;
	case 2:
		result = hpPercent > m_param[1];
		break;
	}

	return result;
}

bool AiCondition::condition2()
{
	return m_aiModule->getTargetOwnTime() >= m_param[0];
}

bool AiCondition::condition3()
{
	Array* arr = m_aiModule->getRoleArray();
	Rect rect(m_param[0], m_param[1], m_param[2], m_param[3]);
	EnumRoleFilter e = m_param[4] ? eRoleFilterPlayer : eRoleFilterMonster;
	int count = 0;
	bool result = false;

	Object* obj;
	AnimationSprite* sp;
	CCARRAY_FOREACH(arr, obj)
	{
		sp = (AnimationSprite*)obj;

		if (sp->getRoleFilter() == e && rect.containsPoint(sp->getCenterPosition()))
		{
			count++;
		}
		switch (m_param[5])
		{
		case 0:
			result = count < m_param[6];
			break;
		case 1:
			result = count == m_param[6];
			break;
		case 2:
			result = count > m_param[6];
			break;
		}
		if (result)
		{
			return true;
		}
	}

	return false;
}
