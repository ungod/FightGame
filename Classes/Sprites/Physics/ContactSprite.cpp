#include "ContactSprite.h"
#include "Box2D/Box2D.h"
#include "Sprites/RoleFilter/RoleFilter.h"
#include "DataManager.h"

ContactSprite::ContactSprite()
{
    m_world = NULL;
	m_body = NULL;
    m_nextCollideTime = 0;
    m_collideRate = 0;
    m_hitMaxNum = 1;
    m_duration = 1.0f;
    m_delayTime = 0;
    m_bodySize = Size(1,1);
	m_bIsBullet = false;
	m_bIsFinish = false;
}

ContactSprite::~ContactSprite()
{
	m_world = NULL;
	m_body = NULL;
}

bool ContactSprite::init()
{
	setTag(CONTACT_TAG);
	return true;
}

 bool ContactSprite::initWithHitBoxID(int ID)
{
    bool bRet = false;
    
    do {

		CC_BREAK_IF(!init());
        CC_BREAK_IF(!HitBox::initWithID(ID));
        
        if(getIsWithAnimation())//有动画就创建
        {
            addChild(getContactAnimateSprite());
        }
        
        bRet = true;
    } while (0);
    
    
    
    
    return bRet;
}

void ContactSprite::updateFixture()
{
    if(getBody() != NULL)
    {
        b2Fixture* fixture = getBody()->GetFixtureList();
        
        b2PolygonShape childShape;
        childShape.SetAsBox(getBodySize().width / 2 / PTM_RATIO, getBodySize().height / 2 / PTM_RATIO);
        
        b2FixtureDef fixtureDef;//身体
        fixtureDef.shape =  &childShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 1.0f;
        fixtureDef.filter.categoryBits = m_categoryBits;
        fixtureDef.filter.maskBits = m_maskBits;
        fixtureDef.isSensor = true;
 
        getBody()->CreateFixture(&fixtureDef);
       
        if(fixture != NULL)
        {
          getBody()->DestroyFixture(fixture);
        }
    }
}

void ContactSprite::initBody()
{
    if((getBodySize().width == 0) || (getBodySize().height == 0))
        return;

	m_world = DataManager::getInstance()->getPhysicsWorld()->getWorld();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = m_bIsBullet;
    
    b2Body* pBody;
	pBody = m_world->CreateBody(&bodyDef);
    setPTMRatio(PTM_RATIO);
    setBody(pBody);//绑定body
    pBody->SetUserData(this);//绑定数据
    
    updateFixture();
   
    pBody->SetTransform(pBody->GetPosition(), 0);//调整角度
}

void ContactSprite::onStarted()
{
    initBody();
}

void ContactSprite::onFinished()//碰撞的结束
{
	if (m_bIsFinish) return;

    stopAllActions();
    if(m_world != NULL && m_body != NULL)//清除box2d的body防止再次发生碰撞
    {
        m_world->DestroyBody(m_body);
        m_body = NULL;
    }
    
    
    if(getContactAnimateSprite() != NULL)//运行消亡动画
    {
        getContactAnimateSprite()->onFinshed();
    }
    
    removeFromParentAndCleanup(true);
	m_bIsFinish = true;
}

void ContactSprite::setX(float x)
{
    m_x = x;
    setPositionX(x);
}

void ContactSprite::setY(float y)
{
    m_y = y;
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    float newY = m_z + y + ground;
    BasePhysicsSprite::setPositionY(newY);
}

void ContactSprite::setZ(float z)
{
    m_z = z;
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    float y = m_y + ground +  z;
    
    BasePhysicsSprite::setPositionY(y);
}


void ContactSprite::setPosition(const Point &position)
{
    updatePosition(position);
}


void ContactSprite::updatePosition(const Point &position)
{
    BasePhysicsSprite::setPosition(position);
    
    float ground = DataManager::getInstance()->getFloorBottom();//地平线
    float maxOrder = DataManager::getInstance()->getMaxZorder();
    int newZorder = maxOrder - ground - m_z;
    
    Node* parent = getParent();
    if(parent != NULL)
    {
        parent->reorderChild(this, newZorder);
    }
    
    
    
    m_x = getPositionX();
    m_z = getPositionY() - ground  - m_y;
    m_y = getPositionY() - ground - m_z;
    
    if(m_body != NULL)
	 m_body->SetAwake(true);//激活b2body，否则碰撞会失效
}


void ContactSprite::updateCollideTime()
{
    m_nextCollideTime = GetCurTime() + getCollideRate();
    
    
    
}

bool ContactSprite::canCollide(bool autoUpdate)
{
    bool bRet = false;
    
    if(GetCurTime() >= m_nextCollideTime)
    {
        bRet = true;
        
        if(autoUpdate)//自动更新下次的时间
        {
          updateCollideTime();        
        }
       //log("updateCollideTime()%f %f",GetCurTime() , getCollideRate());
    }
    
    return bRet;
}


void ContactSprite::onCollsion(AnimationSprite* pTarget)
{
}

void ContactSprite::removeFromParentAndCleanup(bool cleanup)
{
    stopAllActions();

    if (_parent != NULL)
    {
        if(m_world != NULL && m_body != NULL)
        {
            m_world->DestroyBody(m_body);
        }
        _parent->removeChild(this,cleanup);
    }
}

bool ContactSprite::checkCollision(AnimationSprite* pTarget)
{
	bool bRet = false;

	do {

		CC_BREAK_IF(!canCollide());//不在有效的碰撞频率内

		CC_BREAK_IF(!pTarget->canCollide(this));//超出有效的碰撞次数


		float deltaZ = fabs(getZ() - pTarget->getZ());
		if(deltaZ <= getZtolerance())
		{
			bRet = true;
		}

		//log("%f %f %f",pSender->getZ(),pTarget->getZ(),pSender->getZtolerance());

	} while(0);

	return bRet;
}