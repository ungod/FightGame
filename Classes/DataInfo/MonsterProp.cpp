#include "MonsterProp.h"
#include "Sqlite/SqliteResolver.h"

#define INIT_PROP_ENUM_M(var) \
const int MonsterProp::e##var = g_propEnumIndex++

INIT_PROP_ENUM_M(ExpAwarded);
INIT_PROP_ENUM_M(MonsterName);
INIT_PROP_ENUM_M(Type);
INIT_PROP_ENUM_M(Group);
INIT_PROP_ENUM_M(ScriptName);
INIT_PROP_ENUM_M(DialogData);
INIT_PROP_ENUM_M(HeadFigure);

MonsterProp::MonsterProp()
{
	m_aiModuleID = 0;
	m_expAwarded = 0;
	m_monsterName = "";
	m_type = NORMAL_MONSTER;
	m_group = 1;
	m_scriptName = "";
	m_dialogData = "";
	m_headFigure = 0;
}

MonsterProp::~MonsterProp()
{
}

MonsterProp* MonsterProp::createWithResolver( SqliteResolver* sqlRsl )
{
	MonsterProp* role = new MonsterProp;

	if (role && role->initWithResolver(sqlRsl))
	{
		role->autorelease();
		return role;
	}
	CC_SAFE_DELETE(role);
	return NULL;
}

void MonsterProp::parse()
{
	RoleProperty::parse();

	m_aiModuleID = m_sqlRls->getInt("AiModuleID");
	m_expAwardedOrgin = m_sqlRls->getInt("ExpAwarded");
	m_monsterNameOrgin = m_sqlRls->getString("MonsterName");
	m_typeOrgin = m_sqlRls->getInt("Type");
	m_groupOrgin = m_sqlRls->getInt("Group");
	m_scriptNameOrgin = m_sqlRls->getString("ScriptName");
	m_dialogDataOrgin = m_sqlRls->getString("DialogData");
	m_headFigureOrgin = m_sqlRls->getInt("HeadFigure");
}

void MonsterProp::resetWithOrigin()
{
	RoleProperty::resetWithOrigin();

	ASSIGN_BY_ORGIN(m_expAwarded);
	ASSIGN_BY_ORGIN(m_monsterName);
	ASSIGN_BY_ORGIN(m_type);
	ASSIGN_BY_ORGIN(m_group);
	ASSIGN_BY_ORGIN(m_scriptName);
	ASSIGN_BY_ORGIN(m_dialogData);
	ASSIGN_BY_ORGIN(m_headFigure);
}
