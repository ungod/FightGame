#pragma once
#include "cocos2d.h"
#include "Skills/SkillSystem/SkillSystem.h"
#include "BaseSprites/BaseSprite.h"
#include "Box2d/Box2d.h"
#include "AnimateBase/Animate3D.h"
#include "Decoration/ShadowSprite.h"
#include "Skills/SkillAttack/SkillAttackManager.h"
#include "../DataInfo/RoleProperty.h"
USING_NS_CC;
using namespace  std;



/*********
基本的动作角色,涉及物理碰撞类型的,
是所有角色的基础类型

*****/


//@biref 创建角色
//@param __TYPE__ 角色类型
//@param DIR_SRING  string类型的文件夹路径



class AnimationSprite : public Node , public BaseSprite, public Animate3D
{
public:
	AnimationSprite();
	~AnimationSprite(void);
    static AnimationSprite* create(SimpleAnimation* pAnimationSprite);
    bool initWithAnimateAction(SimpleAnimation* pAnimationSprite);
    void addChild(Node* child);
    //scheduled methods
	void update(float dt);


    
    //action methods
	virtual void idle();
	virtual void attack();
	virtual bool hurtWithHitBox(HitBox* hitbox, AnimationSprite* attacker);
	virtual void knockout(); 
	virtual void walkWithDirection(Point direction, float duration = 0, bool isOverride = true);
	virtual void walkWithTarget(Point target, bool isOverride = true);
    virtual void runSkill(Skill* pSkill);
	virtual void runSkillWithIndex(int index);
    virtual void onSkillFinished(Object* pSkill);
    virtual void stopSkills();//停止所有技能;
    
    virtual void onAnimationFinished();
    virtual void playAnimation(const char* aniamtionName, bool loop = false) ;//播放动画
    
    //重载设置位置
    virtual void setPosition(const Point &position);
    virtual void updatePosition(const Point &position);
    virtual Point3D getCenterPosition3D() override;//获取中心点坐标
	virtual Point getCenterPosition();//获取中心坐标XZ
    virtual void setRotation(float fRotation) override;

    
    
    virtual void setCenterToBottom(float var);
    virtual void setCenterToSides(float var);
  
    
    virtual void runSequanceAction(Sequence* action);//运动的系列动作
    virtual void onFallGround();//掉落到地上
    
    
    //刷新fixture
    void updateFixture();
    
    //@brief根据原点和尺寸创建角色的伤害或者攻击框
    //@param origin 中心点的相对位置,零点在角色的几何中心点
    //@size 框的尺寸,width:框 height:高
    //@return 返回的之中有两个框:
    //1.cocos2d::CCRect actual  actual框是相对于整个世界坐标的
	//2.cocos2d::CCRect original origin是相对于角色几何中心点的
    BoundingBox createBoundingBoxWithOrigin(Point origin, Size size);
	
    
    //@brief 每帧动画中,由于角色走动,攻击框和伤害框会发生相对位移,这里做相应的处理
    void transformBoxes();
    
    
    //@技能列表
    CC_SYNTHESIZE_RETAIN(SkillAttackManager*, m_skillListManager ,SkillListManager);
    
    CC_SYNTHESIZE(ShadowSprite*, m_shadow, Shadow);//影子
    
    //@brief 角色的活动状态
    CC_SYNTHESIZE(bool, m_active, Active);

    //@brief 每个角色中的核心人物,一般的角色可能在头顶有血条,名称等信息
    //这里的是角色的人物
    CC_SYNTHESIZE(SimpleAnimation*, m_animationSprite, AnimateSprite);//角色
    
    
    //@brief 角色在使用的技能数据,会根据实际的情况动态增减
    CC_SYNTHESIZE(Array*, m_skillArray, SkillArray);
    
    //@brief 角色在box2d物理世界中的body
    CC_SYNTHESIZE(b2Body*, m_body, Body);
    
    
    //states
	CC_SYNTHESIZE(ActionState, m_actionState, ActionState);//动作状态
    
    
    //角色在行走的时候期望的位置,因为考虑到可能会走出边界
	CC_SYNTHESIZE(Point, m_desiredPosition, DesiredPosition);

	//移动的增量修正
	CC_SYNTHESIZE(Point, m_incFix, IncFix);

    //角色面部朝向,player当前面朝向x:大于0为向右,小于0为向左  y:大于0向上,小于0向下
	Point getFaceDirection(){ return m_faceDirection; }
	void setFaceDirection(const Point& face)
	{
		m_faceDirection = Point(INT_SIGN(face.x), INT_SIGN(face.y));
		setScaleX(fabs(getScaleX())*INT_SIGN(face.x));
	}

	//角色属性
	RoleProperty* getRoleProperty(){ return m_roleProp; }
	void setRoleProperty(RoleProperty* v);
    
    //@brief当前正在使用的技能
    CC_SYNTHESIZE(SkillSystem*, m_currentSkill, CurrentSkill);
    
    //@biref 角色类型的归类
    //主要有两种类型:
    //1.player
    //2.monter
    EnumRoleFilter getRoleFilter(){return m_roleFilter;}
    void setRoleFilter(EnumRoleFilter filter);
    
    
    virtual void setX(float x);//x坐标
    virtual void setY(float y);//y坐标
    virtual void setZ(float z);//z坐标
    
 protected:
	Point m_faceDirection;

    EnumRoleFilter m_roleFilter;
    RoleProperty* m_roleProp;

	Point m_targetPoint;
    float m_walkDuration;
	float m_walkElapse;
	bool  m_bCanWalkOverride;
};
