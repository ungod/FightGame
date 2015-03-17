#pragma once
#include "cocos2d.h"
#include "Geometries/Point3d.h"
#include "Geometries/BodyRegion.h"
USING_NS_CC;
using namespace std;

class BaseHitBox
{
public:
    
    BaseHitBox();
    ~BaseHitBox();
    
    //@brief 是否有同步动画
    CC_SYNTHESIZE(bool, m_isWithAnimation, IsWithAnimation);
    
    //运行的延迟事件
    //@Param m_duration 单位:秒
    CC_SYNTHESIZE(float, m_delayTime, DelayTime);
    
    //运行的最大生命周期
    //@Param m_duration 单位:秒
    CC_SYNTHESIZE(float, m_duration, Duration);
    
    
    //@brief 碰撞最大频率, 每次碰撞的最小时间间隔 单位:秒/次
    CC_SYNTHESIZE(double, m_collideRate, CollideRate);
    
    //最大攻击次数
    CC_SYNTHESIZE(int, m_hitMaxNum, HitMaxNum);
    
    //对单个角色的最大攻击次数
    CC_SYNTHESIZE(int, m_hitSingleMaxNum, HitSingleMaxNum);
    
    //@brief 大小尺寸,指的是x和y方向的尺寸
    CC_SYNTHESIZE(Size, m_bodySize, BodySize);
    
    //@brief 出现位置相对于技能使用者的区域位置
    CC_SYNTHESIZE(BodyRegion::Region, m_aPPearRegion, AppearRegion);
    
    //@brief 产生的位置,相对AppearRegion的位置
    CC_SYNTHESIZE(Point3D, m_aPPearPosition, AppearPosition);

    //@brief 可产生碰撞的范围,以碰撞框位置为中心,z轴前后的距离
    CC_SYNTHESIZE(float, m_ztolerance, Ztolerance);
    
    //@brief 配置动画的名称,这个是armature中动画的名称,务必对应起来
    CC_SYNTHESIZE(int, m_animationID, AnimationID);
    
    //@brief 运行时播放的音乐文件
    CC_SYNTHESIZE(int, m_idleMusicID, IdleMusicID);
    
    //@brief 碰撞的时候播放的音乐文件
    CC_SYNTHESIZE(int, m_onCollisionMusicID, OnCollisionMusicID);
    
    //@brief 小时音效
    CC_SYNTHESIZE(int, m_disappearMusicID, DisappearMusicID);
    
    //@brief 移动的路径曲线,位置信息为每次的相对位置
    //配置文件的样式为:<string>{{0.4},{100,200,0}}</string>
    //意义分别为时间(time:秒为单位)和坐标点(point3D),然后产生的Sequace Action
    CC_SYNTHESIZE_RETAIN(Sequence*, m_motionCurve, MotionCurve);
    
    //@brief 碰撞的时候,碰撞框的运动轨迹,为NULL的时候不改变
    CC_SYNTHESIZE_RETAIN(Sequence*, m_onCollisionMotionCurve, OnCollisionMotionCurve);
    
    //@breif 碰撞的时候显示的动画动作名称
    CC_SYNTHESIZE(string, m_collisionAnimation, CollisionAnimation);
    //@breif 碰撞的时候显示的动画动作ID
    CC_SYNTHESIZE(int, m_collisionAnimationID, CollisionAnimationID);    
    //@brief 碰撞时动画在角色播放的区域
    CC_SYNTHESIZE(BodyRegion::Region, m_collisionAnimationRegion, CollisionAnimationRegion);
    //@brief 碰撞时动画在角色播放的相对位置
    CC_SYNTHESIZE(Point3D, m_collisionAnimationPos, CollisionAnimationPos);
    
    
    //@brief 碰撞的时候,攻击者的运动轨迹
    CC_SYNTHESIZE_RETAIN(Sequence*, m_onCollisionAttackerMotionCurve, OnCollisionAttackerMotionCurve);
    
    
    //@brief  碰撞的时候 被攻击者的运动轨迹
    CC_SYNTHESIZE_RETAIN(Sequence*, m_onCollisionInjuredMotionCurve, OnCollisionInjuredMotionCurve);
    
	//Damage = (DamageConstantWithAP + Level*DamageFactorWithAP)*AP + DamageConstant + Level*DamageFactor
	CC_SYNTHESIZE(int, m_damageConstantWithAP, DamageConstantWithAP);

	CC_SYNTHESIZE(float, m_damageFactorWithAP, DamageFactorWithAP);

	CC_SYNTHESIZE(float, m_damageConstant, DamageConstant);

	CC_SYNTHESIZE(float, m_damageFactor, DamageFactor);
};