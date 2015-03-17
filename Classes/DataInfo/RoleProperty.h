#pragma once

#include "cocos2d.h"
#include "string"
#include "Sqlite/SqliteResolver.h"

USING_NS_CC;
using namespace std;

extern int g_propEnumIndex;

//声明包含属性枚举和属性更新派发的变量
#define PROPERTY_SYNTHESIZE(varType, varName, funName)\
public: static const int e##funName;\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var)\
{\
	varName = var;\
	this->dispatch(e##funName);\
}\

//声明属性原值和新值。
//原值指职业、怪物的最基础属性。
//新值指装备、Buff后的值。
//保留原值用于随时计算属性新值。
#define PROPERTY_WITH_ORIGIN(varType, varName, funName)\
CC_SYNTHESIZE_READONLY(varType, varName##Orgin, funName##Orgin)\
PROPERTY_SYNTHESIZE(varType, varName, funName)\

#define ASSIGN_BY_ORGIN(var) var = var##Orgin

//暴击系数，固定值
#define CRITICAL_HIT_FACTOR 2
#define PROP_SIZE 50

class RoleProperty;

typedef function<void(RoleProperty*)> PropDelegate;
typedef vector<PropDelegate> PropCallList;

/************************************************************************
*基本角色属性基类
*本类及其派生类包含所有角色属性、公式运算、结果数据
************************************************************************/

class RoleProperty : public Object
{
public:
	RoleProperty();
	~RoleProperty();

	bool initWithResolver(SqliteResolver* dict);

	virtual void parse();
	virtual void resetWithOrigin();

	virtual void updateProp();

	//当任意属性的值被修改时回调
	//考虑性能没用notification
	//可以使用addCallback(CC_CALLBACK_1(...), eCurrentHP)来增加HP更新监听
	virtual void addCallback(PropDelegate ob, int propName);
	virtual void removeCallback(PropDelegate ob, int propName);
	inline virtual void dispatch(int propName);

	/*
	* 公式运算
	*/

	//计算技能伤害
	int skillDamageFromConstantAndFactor( int damageConstantWithAP, int damageFactorWithAP, int damageConstant, int damageFactor );

	//计算最终伤害，并更新血量
	//@param damage 来源的伤害原始值（技能初始伤害）
	//@param isCritical 是否有暴击
	virtual int damageFromTarget(RoleProperty* from, int damage, bool isCritical);

	//计算伤害减免
	//@param 攻击方属性
	virtual float damageReductionFromTarget(RoleProperty* from);

	//计算最终成功命中几率
	//@param 目标属性
	virtual float finalHitRateToTarget(RoleProperty* target);

	//@brief 角色资源ID
	CC_SYNTHESIZE_READONLY(int, m_rolesID, RolesID);

	CC_SYNTHESIZE_READONLY(string, m_name, Name);

	//@brief 编号
	CC_SYNTHESIZE_READONLY(int, m_ID, ID);

	/*
	* 原始属性。包含初始值和计算后的新值
	*/
	//@brief 等级
	PROPERTY_WITH_ORIGIN(int, m_level, Level);

	//@brief 最大HP
	PROPERTY_WITH_ORIGIN(int, m_maxHP, MaxHP);

	//@brief 最大MP
	PROPERTY_WITH_ORIGIN(int, m_maxMP, MaxMP);

	//@brief 攻击力
	PROPERTY_WITH_ORIGIN(int, m_attack, Attack);

	//@brief 防御力
	PROPERTY_WITH_ORIGIN(int, m_defence, Defence);

	//@brief 暴击
	PROPERTY_WITH_ORIGIN(int, m_criticalHit, CriticalHit);

	//@brief 命中
	PROPERTY_WITH_ORIGIN(int, m_hitRate, HitRate);

	//@brief 闪避
	PROPERTY_WITH_ORIGIN(int, m_dodge, Dodge);

	//@brief 内力
	PROPERTY_WITH_ORIGIN(int, m_internalForce, InternalForce);

	//@brief 移动速度
	PROPERTY_WITH_ORIGIN(Point, m_walkSpeed, WalkSpeed);

	//@brief 攻击速度
	PROPERTY_WITH_ORIGIN(int, m_attackSpeed, AttackSpeed);

    
    //@brief 技能列表
    CC_SYNTHESIZE(int, m_skillListID, SkillListID);
    
	/*
	* 结果属性。不包含原始值但能通过其他值计算获得新值。
	*/
	//@brief 当前HP
	PROPERTY_SYNTHESIZE(int, m_currentHP, CurrentHP);

	//@brief 当前MP（真气）
	PROPERTY_SYNTHESIZE(int, m_currentMP, CurrentMP);

	//@brief 当前HP百分比
	CC_SYNTHESIZE_READONLY(float, m_currentHPPercent, CurrentHPPercent);

	//@brief 当前MP百分比
	CC_SYNTHESIZE_READONLY(float, m_currentMPPercent, CurrentMPPercent);

	//@brief 暴击几率
	CC_SYNTHESIZE_READONLY(float, m_criticalHitOdds, CriticalHitOdds);

	//@brief 命中率
	CC_SYNTHESIZE_READONLY(float, m_hitRateOdds, HitRateOdds);

	//@brief 闪避率
	CC_SYNTHESIZE_READONLY(float, m_dodgeOdds, DodgeOdds);

	//@brief 真气恢复
	CC_SYNTHESIZE_READONLY(float, m_mpRecover, MpRecover);
    


protected:
	SqliteResolver* m_sqlRls;
	PropCallList* m_observers[PROP_SIZE];
};