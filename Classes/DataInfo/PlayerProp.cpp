
#include "PlayerProp.h"

#define INIT_PROP_ENUM_P(var)\
const int PlayerProp::e##var = g_propEnumIndex++

INIT_PROP_ENUM_P(Experience);

PlayerProp::PlayerProp()
{
	m_experience = 0;
    m_attackListID = 0;
}

PlayerProp::~PlayerProp()
{

}

PlayerProp* PlayerProp::createWithResolver( SqliteResolver* sqlRls )
{
	PlayerProp* role = new PlayerProp;

	if (role && role->initWithResolver(sqlRls))
	{
		role->autorelease();
		return role;
	}
	CC_SAFE_DELETE(role);
	return NULL;
}

void PlayerProp::parse()
{
	RoleProperty::parse();

	m_experienceOrgin = m_sqlRls->getInt("Experience");
    m_attackListID = m_sqlRls->getInt("AttackListID");
}

void PlayerProp::resetWithOrigin()
{
	RoleProperty::resetWithOrigin();
	
	ASSIGN_BY_ORGIN(m_experience);
}

