#include "RoleProperty.h"
#include "Utils/MathUtils.h"

int g_propEnumIndex = 0;

#define INIT_PROP_ENUM(var)\
const int RoleProperty::e##var = g_propEnumIndex++

//初始化属性标识符，用于监听该属性回调
INIT_PROP_ENUM(Level);
INIT_PROP_ENUM(CurrentHP);
INIT_PROP_ENUM(CurrentMP);
INIT_PROP_ENUM(MaxHP);
INIT_PROP_ENUM(MaxMP);
INIT_PROP_ENUM(Attack);
INIT_PROP_ENUM(Defence);
INIT_PROP_ENUM(CriticalHit);
INIT_PROP_ENUM(HitRate);
INIT_PROP_ENUM(Dodge);
INIT_PROP_ENUM(InternalForce);
INIT_PROP_ENUM(WalkSpeed);
INIT_PROP_ENUM(AttackSpeed);

RoleProperty::RoleProperty()
{
	m_rolesID = 0;
	m_ID = -1;
	m_levelOrgin = 1;
	m_currentHP = -1;
	m_currentMP = -1;
	m_maxHPOrgin = 100;
	m_maxMPOrgin = 10;
	m_attackOrgin = 10;
	m_criticalHitOrgin = 0;
	m_hitRateOrgin = 100;
	m_dodgeOrgin = 0;
	m_internalForceOrgin = 0; 
	m_walkSpeedOrgin = Point(1, 1);
	m_attackSpeedOrgin = 1;
    m_skillListID = 0;

	m_name = "";

	for (int i=0; i<PROP_SIZE; i++)
	{
		m_observers[i] = NULL;
	}
}

RoleProperty::~RoleProperty()
{
	for (int i=0; i<PROP_SIZE; i++)
	{
		if (m_observers[i] != NULL)
		{
			delete m_observers[i];
			m_observers[i] = NULL;
		}
	}
    
}

bool RoleProperty::initWithResolver( SqliteResolver* sqlRls )
{
	if (!sqlRls)
		return false;

	m_sqlRls = sqlRls;
	m_sqlRls->retain();

	parse();
	resetWithOrigin();
	updateProp();

	return true;
}

void RoleProperty::parse()
{
	m_rolesID	= m_sqlRls->getInt("RolesID");
	m_name		= m_sqlRls->getString("Name");
	m_ID		= m_sqlRls->getInt("ID");

	m_maxHPOrgin = m_sqlRls->getInt("HP");
	m_maxMPOrgin = m_sqlRls->getInt("MP");

	m_attackOrgin		= m_sqlRls->getInt("Attack");
	m_defenceOrgin		= m_sqlRls->getInt("Defense");
	m_criticalHitOrgin	= m_sqlRls->getInt("CriticalHit");
	m_hitRateOrgin		= m_sqlRls->getInt("HitRate");
	m_dodgeOrgin		= m_sqlRls->getInt("Dodge");
	m_internalForce		= m_sqlRls->getInt("InternalForce");
	m_walkSpeedOrgin	= m_sqlRls->getSize("WalkSpeed");
    m_skillListID          = m_sqlRls->getInt("SkillListID");
}

void RoleProperty::resetWithOrigin()
{
	ASSIGN_BY_ORGIN(m_level);
	ASSIGN_BY_ORGIN(m_maxHP);
	ASSIGN_BY_ORGIN(m_maxMP);
	ASSIGN_BY_ORGIN(m_attack);
	ASSIGN_BY_ORGIN(m_defence);
	ASSIGN_BY_ORGIN(m_criticalHit);
	ASSIGN_BY_ORGIN(m_hitRate);
	ASSIGN_BY_ORGIN(m_dodge);
	ASSIGN_BY_ORGIN(m_internalForce);
	ASSIGN_BY_ORGIN(m_walkSpeed);
	ASSIGN_BY_ORGIN(m_attackSpeed);
}

void RoleProperty::updateProp()
{
	//TODO 当前生命的运算
	m_currentHP = m_maxHP;
	m_currentMP = m_maxMP;

	//攻击力=角色属性提升攻击力+装备提升攻击力+被动技能提升攻击力
	m_attack = m_attack + 0 + 0;

	m_criticalHitOdds = (float)m_criticalHit / (m_level*100);
	m_hitRateOdds = (float)m_hitRate / (m_level*100) + 0.75;
	m_dodgeOdds = (float)m_dodge / (m_level*100);
	m_mpRecover = (float)m_internalForce / 200;
}

int RoleProperty::skillDamageFromConstantAndFactor( int damageConstantWithAP, int damageFactorWithAP, int damageConstant, int damageFactor )
{
	return m_attack*(damageConstantWithAP + m_level*damageFactorWithAP) + (damageConstant + m_level*damageFactor);
}

int RoleProperty::damageFromTarget( RoleProperty* from,  int damage, bool isCritical)
{
	return damage * (1-damageReductionFromTarget(from)) * (1+CRITICAL_HIT_FACTOR*int(isCritical)) * (float(randomRange(90, 110))/100);
}

float RoleProperty::damageReductionFromTarget( RoleProperty* from )
{
	return (float)m_defence / (from->m_level*100);
}

float RoleProperty::finalHitRateToTarget( RoleProperty* target )
{
	return (float(m_hitRate)/m_level*90/((float(m_dodge)/target->m_level+90)*100+0.75f)) * (1+float(m_level-target->m_level)/1000);
}

void RoleProperty::addCallback( PropDelegate ob, int propName )
{
	if (m_observers[propName] == NULL)
	{
		m_observers[propName] = new PropCallList;
	}
	m_observers[propName]->push_back(ob);
}

void RoleProperty::removeCallback( PropDelegate ob, int propName )
{
	PropCallList* vec = m_observers[propName];
	PropCallList::iterator it;
	for (it = vec->begin(); it != vec->end(); it++)
	{
		if (&*it == &ob)
		{
			it = vec->erase(it);
			break;
		}
	}
}

void RoleProperty::dispatch(int propName)
{
	if (m_observers[propName] == NULL)
		return;

	PropCallList* vec = m_observers[propName];
	PropCallList::iterator it;
	for (it = vec->begin(); it != vec->end(); it++)
	{
		(*it)(this);
	}
}