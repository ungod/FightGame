#include "AnimationSprite.h"
#include "DataManager.h"
#include "EntitiesManager.h"
#include "cocos-ext.h"
#include "CCArmature/CCArmature.h"
#include "CCArmature/CCBone.h"
#include "Sprites/RoleFilter/RoleFilter.h"
#include "Decoration/NoteSprite.h"

USING_NS_CC_EXT;
/***
 m_animationSpritede 位置默认为ccp(0,0);
 通用的角色
 
 
 ****/

AnimationSprite::AnimationSprite()
{
    m_active = true;
    m_shadow = NULL;
    
    m_skillArray = NULL;
    m_body = NULL;
    m_currentSkill = NULL;
    m_faceDirection = Point(1, 0);//初始为向右
    m_roleFilter = eRoleFilterPlayer;//默认为player
    m_skillListManager = NULL;

	m_targetPoint = INFINITE_POINT;
	m_walkDuration = 0;
	m_walkElapse = 0;
	m_bCanWalkOverride = true;
	m_incFix = Point(1, 1);

	m_roleProp = NULL;

    this->setScale(SCALE_FACTOR);
}


AnimationSprite::~AnimationSprite()
{
    unscheduleUpdate();
    stopSkills();
    CC_SAFE_RELEASE(m_skillArray);
    CC_SAFE_RELEASE(m_skillListManager);
	CC_SAFE_RELEASE(m_roleProp);

}


AnimationSprite* AnimationSprite::create(SimpleAnimation* pAnimationSprite)
{
    AnimationSprite* pRet = new AnimationSprite();
    if(pRet && pRet->initWithAnimateAction(pAnimationSprite))
    {
        pRet->autorelease();
    
    }

    
    return pRet;
}



bool AnimationSprite::initWithAnimateAction(SimpleAnimation* pAnimationSprite)
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(pAnimationSprite == NULL);
        m_animationSprite = pAnimationSprite;
        addChild(pAnimationSprite);
        pAnimationSprite->setFather(this);
        
        CC_BREAK_IF(!CCNode::init());
        
        m_skillArray = CCArray::create();
        CC_BREAK_IF(!m_skillArray);
        m_skillArray->retain();
        
               
        setCenterToBottom(m_animationSprite->getContentSize().height / 2);
        setCenterToSides(m_animationSprite->getContentSize().width / 2);
        setHitbox(createBoundingBoxWithOrigin(Point(-getCenterToSides(), -getCenterToBottom()),Size(getCenterToSides() * 2, getCenterToBottom() * 2)));
  
        
		if (DataManager::getInstance()->getPhysicsEnable())
		{
			b2World* world = DataManager::getInstance()->getPhysicsWorld()->getWorld();

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
			bodyDef.userData = this;
			m_body = world->CreateBody(&bodyDef);

			float offset = m_shadow ? m_shadow->getRelativePos().y : 0;//必须加上阴影体积的碰撞，否则三维碰撞结果不准确
			float heightOffset = m_shadow ? m_shadow->getExpectSize().height/8 : 0;

			b2PolygonShape shape;
			shape.SetAsBox(m_centerToSides / PTM_RATIO, (m_centerToBottom + heightOffset) / PTM_RATIO, b2Vec2(0, offset / PTM_RATIO), 0);

			b2FixtureDef fixtureDef;//身体
			fixtureDef.shape =  &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.isSensor = true;
			m_body->CreateFixture(&fixtureDef);
		}
        
        idle();
        scheduleUpdate();
        
        
        bRet = true;
    } while (0);


    return bRet;
}





void AnimationSprite::updateFixture()
{
    if(m_body != NULL)
    {
        b2Fixture* fixture = m_body->GetFixtureList();
        CCAssert(fixture != NULL, "fixure is NULL");
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = fixture->GetShape();
        fixtureDef.userData = fixture->GetUserData();
        fixtureDef.friction = fixture->GetFriction();
        fixtureDef.restitution = fixture->GetRestitution();
        fixtureDef.density = fixture->GetDensity();
        fixtureDef.isSensor = fixture->IsSensor();
        fixtureDef.filter = fixture->GetFilterData();
        
		float offset = m_shadow ? m_shadow->getRelativePos().y : 0;//必须加上阴影体积的碰撞，否则三维碰撞结果不准确
		float heightOffset = m_shadow ? m_shadow->getExpectSize().height/8 : 0;

		b2PolygonShape shape;
		shape.SetAsBox(m_centerToSides / PTM_RATIO, (m_centerToBottom + heightOffset) / PTM_RATIO, b2Vec2(0, offset / PTM_RATIO), 0);

        fixtureDef.shape = &shape;
        
        m_body->CreateFixture(&fixtureDef);
        m_body->DestroyFixture(fixture);

    }
}


void AnimationSprite::setCenterToBottom(float var)
{
    m_centerToBottom = var;
    updateFixture();
    
}

void AnimationSprite::setCenterToSides(float var)
{
    m_centerToSides = var;
    updateFixture();
}


void AnimationSprite::addChild(Node* child)
{
    CCNode::addChild(child);

}


void AnimationSprite::idle()
{
    CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");
    
    if(!getActive())
        return;
    
    if (m_actionState != kActionStateIdle)
	{
		m_animationSprite->playAnimation(SPRITE_IDLE,true);
		m_actionState = kActionStateIdle;
		m_velocity = Point(0,0);
        
	}
    m_bCanWalkOverride = true;
    
}



bool AnimationSprite::hurtWithHitBox(HitBox* hitbox, AnimationSprite* attacker)
{
	CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");

	Sprite* sp;
	RoleProperty* attackProp = attacker->getRoleProperty();

	int damage = attackProp->skillDamageFromConstantAndFactor(hitbox->getDamageConstantWithAP(),
														hitbox->getDamageFactorWithAP(),
														hitbox->getDamageConstant(),
														hitbox->getDamageFactorWithAP());

	if (m_actionState != kActionStateKnockedOut)
	{
		if (rand()%100 < attackProp->finalHitRateToTarget(m_roleProp)*100)
		{
			int finalDamage;

			if (rand()%100 < attackProp->getCriticalHitOdds()*100)
			{
				finalDamage = m_roleProp->damageFromTarget(attacker->getRoleProperty(), damage, true);
				sp = NoteSprite::createWithSpriteFrameName(CRITICAL_PNG);
				DataManager::getInstance()->getHudLayer()->addChild(sp);
				sp->setPosition(convertToWorldSpace(Point::ZERO));
			}
			else
			{
				finalDamage = m_roleProp->damageFromTarget(attacker->getRoleProperty(), damage, false);
			}

			this->setScaleX(-attacker->getScaleX());//面对攻击者
			m_animationSprite->playAnimation(SPRITe_HURT);;
			m_actionState = kActionStateHurt;
			m_roleProp->setCurrentHP(m_roleProp->getCurrentHP()-finalDamage);

			sp = NoteSprite::createNum(finalDamage);
			DataManager::getInstance()->getHudLayer()->addChild(sp);
			sp->setPosition(convertToWorldSpace(Point::ZERO));

			if (m_roleProp->getCurrentHP() <= 0 )
			{
				m_actionState = kActionStateKnockedOut;
				DataManager::getInstance()->getPhysicsWorld()->getWorld()->DestroyBody(m_body);//先删除,防止再次检测
				m_body = NULL;
			}
		}
		else
		{
			sp = NoteSprite::createWithSpriteFrameName(MISS_ICON_PNG);
			DataManager::getInstance()->getHudLayer()->addChild(sp);
			sp->setPosition(convertToWorldSpace(Point::ZERO));
			return false;
		}
		
    }
    
    return true;
    
}

void AnimationSprite::playAnimation(const char* aniamtionName, bool loop)
{
    getAnimateSprite()->playAnimation(aniamtionName, loop);
}



void AnimationSprite::runSequanceAction(Sequence* action)
{
    stopAllActions();
    setActive(false);
    
    runActionWithLanding(action);
    
}



void AnimationSprite::onFallGround()
{
    setActive(true);
    if (m_roleProp->getCurrentHP() <= 0 )
    {
        knockout();
    }
    
    else
    {
      idle();
    }

    
}


void AnimationSprite::knockout()
{
   CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");
   
    DataManager::getInstance()->getGameLayer()->getEntitiesManager()->removeChild(this);
    m_animationSprite->removeFromParentAndCleanup(true);
	m_actionState = kActionStateKnockedOut;
}

void AnimationSprite::attack()
{
    
    
}



void AnimationSprite::runSkill(Skill* pSkill)
{
    if(!getActive())
        return;
    
    if(pSkill == NULL)
        return;
    
    if(pSkill->getSkillItem() != NULL)
    {
        pSkill->getSkillItem()->onSkillStarted();
    }    
    
    m_currentSkill = dynamic_cast<SkillSystem*>(pSkill);
            
    if(m_actionState != kActionStateAttack)
        m_actionState = kActionStateRunSkill;
    
    pSkill->startSkillWithOwner(this, getFaceDirection());
    pSkill->setFinishedCallback(this, callfuncO_selector(AnimationSprite::onSkillFinished));//设置技能播放完后回调
    m_skillArray->addObject(pSkill);
}

void AnimationSprite::runSkillWithIndex( int index )
{
	runSkill(m_skillListManager->getSkillAtIndex(index));
}

void AnimationSprite::stopSkills()
{
    Object* obj;
    CCARRAY_FOREACH_REVERSE(m_skillArray, obj)
    {
        Skill* skill = dynamic_cast<Skill*>(obj);
        skill->removeSkills();
    }
  
    
}



void AnimationSprite::onSkillFinished(Object* pSkill)//技能动作生命完毕
{
    Skill* skill = (Skill*)pSkill;
    
    m_currentSkill = NULL;
    
    if(skill->getSkillItem() != NULL)
    {
      skill->getSkillItem()->onSkillFinished();//通知菜单动作完成
    }
    
    m_skillArray->removeObject(pSkill);//从列表中删除技能

}

void AnimationSprite::onAnimationFinished()
{
    //CCNode* sprite = (CCNode*)pSender;
    if(m_actionState == kActionStateRunSkill)//角色动画的完成
    {
        //log("skill animation finished");
        onSkillAnimationFinished();

    }
    
    else if(m_actionState == kActionStateAttack)
    {
      //log("attack finished");
        onAttackAnimationFinished();
    }

	if (m_actionState == kActionStateWalk)//移动状态应该持续播放不进入idle
	{
		m_animationSprite->playAnimation(SPRITE_WALK);
	}
	else
	{
		idle();
	}
    
}


void AnimationSprite::setRoleFilter(EnumRoleFilter filter)
{
    if(m_body != NULL)
    {
        b2Filter tmpFilter = m_body->GetFixtureList()->GetFilterData();
        tmpFilter.categoryBits = RoleFilter::getFilter(filter).categoryBits;
        tmpFilter.maskBits = RoleFilter::getFilter(filter).maskBits;
        
        m_body->GetFixtureList()->SetFilterData(tmpFilter);
    }
    
    
    m_roleFilter = filter;
}





BoundingBox AnimationSprite::createBoundingBoxWithOrigin(Point origin, Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = getPosition() + Point(boundingBox.original.origin.x, boundingBox.original.origin.y);
	boundingBox.actual.size = size;
	return boundingBox;
}


void AnimationSprite::update(float dt)
{
    CCNode::update(dt);
    
    if(!getActive())
        return;

	if (!m_targetPoint.equals(INFINITE_POINT) && (int)(getCenterPosition() - m_targetPoint).getLength() <= 0)
	{
		m_targetPoint = INFINITE_POINT;
		idle();
	}
	if (m_walkDuration > FLT_EPSILON && m_walkElapse >= m_walkDuration)
	{
		m_walkDuration = 0;
		idle();
	}
    
    if (m_actionState == kActionStateWalk)
	{
		Point fixedVec = Point(m_incFix.x * m_velocity.x, m_incFix.y * m_velocity.y);
		m_desiredPosition = getPosition() + fixedVec * dt;//注意这里使用的是parent的position
		m_walkElapse += dt;
        
		m_incFix = Point(1, 1);
        updatePosition(m_desiredPosition);
    }
    
    
}



void AnimationSprite::walkWithDirection(Point direction, float duration, bool isOverride)
{
    CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");

	if(!getActive())
		return;

	//不覆盖状态下，只覆盖可覆盖的；覆盖状态下，始终覆盖。
	if (!isOverride && !m_bCanWalkOverride)
		return;

	m_bCanWalkOverride = !isOverride;
	m_walkDuration = duration;
	m_walkElapse = 0;

	if (m_actionState == kActionStateIdle)
	{
		m_animationSprite->playAnimation(SPRITE_WALK);
		m_actionState = kActionStateWalk;
	}
	if (m_actionState == kActionStateWalk)
	{
		Point wspeed = m_roleProp->getWalkSpeed();
		m_velocity = Point(direction.x * wspeed.x, direction.y * wspeed.y);
		setFaceDirection(m_velocity);//更改面朝向
	}
}


void AnimationSprite::walkWithTarget( Point target , bool isOverride)
{
	if (m_targetPoint.equals(target) || target.equals(getCenterPosition()))
		return;

	if (!isOverride && !m_bCanWalkOverride)
		return;

	m_bCanWalkOverride = !isOverride;
	m_targetPoint = target;

	Point vec = m_targetPoint - getCenterPosition();
	walkWithDirection(vec.normalize(), 0, isOverride);
}


void AnimationSprite::updatePosition(const Point &position)
{
    
    float extraHeight = 0;
    if(m_shadow != NULL)
    {
        extraHeight = m_shadow->getRelativePos().y ;//影子偏移高
        
    }
    
    float floorBottom = DataManager::getInstance()->getFloorBottom();
    float floorTop = DataManager::getInstance()->getFloorTop();
    
    float posX = clampf(position.x, getCenterToSides(), DataManager::getInstance()->getMapWidth() - getCenterToSides());
    float posZ = clampf(position.y, getCenterToBottom() + floorBottom + m_y - extraHeight, floorTop + getCenterToBottom() + m_y - extraHeight);
    
    Point newPosition(posX, posZ);
    CCNode::setPosition(newPosition);
    transformBoxes();
    
    float maxOrder = DataManager::getInstance()->getMaxZorder();
    int newZorder = maxOrder - (newPosition.y - getCenterToBottom()) + m_y - extraHeight;//z阻挡以影子为基准线
    
    Node* parent = getParent();
    if(parent != NULL)
    {
        parent->reorderChild(this, newZorder);
    }
    
    
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    m_x = getPositionX()- getCenterToSides();
    m_z = getPositionY() - ground - getCenterToBottom() - m_y;
    m_y = getPositionY() - getCenterToBottom() - ground - m_z;
    
    if(m_shadow != NULL)
    {
        extraHeight = m_shadow->getRelativePos().y;
        
        m_z += extraHeight;
        
        float scaleX = m_shadow->getExpectSize().width / (m_shadow->getContentSize().width + m_y/4)/ SCALE_FACTOR;
        float scaleY = m_shadow->getExpectSize().height / (m_shadow->getContentSize().height + m_y/4) / SCALE_FACTOR;
        m_shadow->setScaleX(scaleX);
        m_shadow->setScaleY(scaleY);
        
        m_shadow->setPosition( Point(m_shadow->getRelativePos().x , -m_y  - getCenterToBottom() + m_shadow->getRelativePos().y) / SCALE_FACTOR);
    }
    
    if(m_body != NULL)
     m_body->SetAwake(true);//激活b2body，否则碰撞会失效
 }


void AnimationSprite::transformBoxes()
{
	m_hitBox.actual.origin = getPosition() + Point(m_hitBox.original.origin.x, m_hitBox.original.origin.y);
    
    if(m_body != NULL)
    {
        b2Vec2 vec = b2Vec2(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
        m_body->SetTransform(vec, CC_DEGREES_TO_RADIANS(getRotation()));
        
    }
}




void AnimationSprite::setRotation(float fRotation)
{
    Node::setRotation(fRotation);
   
    if(m_body != NULL)
    {
    
      b2Vec2 pos = b2Vec2(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
      float radians = CC_DEGREES_TO_RADIANS(fRotation);
   
      m_body->SetTransform(pos, radians);
    }
    
    
}


void AnimationSprite::setPosition(const Point &position)
{
    updatePosition(position);
}



void AnimationSprite::setX(float x)
{
    m_x = x;
    Node::setPositionX(x + getCenterToSides());
}

void AnimationSprite::setY(float y)
{
    m_y = y;
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    float newY = m_z + y + ground + getCenterToBottom();
    if(m_shadow != NULL)
    {
        float extraHeight = m_shadow->getRelativePos().y;
        newY -= extraHeight;
    }
    
    Node::setPositionY(newY);
}

void AnimationSprite::setZ(float z)
{
    m_z = z;
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    float y = m_y + ground + getCenterToBottom() + z;
    

    if(m_shadow != NULL)
    {
        float extraHeight = m_shadow->getRelativePos().y;
        y -= extraHeight;//以影子为基础
    }

    Node::setPositionY(y);
}


Point3D AnimationSprite::getCenterPosition3D()
{

    float centerX = m_x + getCenterToSides();
    float centerY = m_y + getCenterToBottom();
    float centerZ = m_z;
    if(m_shadow != NULL)
    {
        float extraHeight = m_shadow->getRelativePos().y;
        centerY -= extraHeight;//消除影子高度的影响
    }
    //log("%f %f %f",centerX, centerY, centerZ);

    return Point3D(centerX, centerY, centerZ);
}

Point AnimationSprite::getCenterPosition()
{
	Point3D p = getCenterPosition3D();
	return Point(p.x, p.z);
}

void AnimationSprite::setRoleProperty( RoleProperty* v )
{
	if (v)
	{
		m_roleProp = v;
		m_roleProp->retain();
	}
}













