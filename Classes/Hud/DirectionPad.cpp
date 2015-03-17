#include "Hud/DirectionPad.h"
#include "../Includes/Resources.h"

USING_NS_CC;

DirectionPad::DirectionPad(void)
{
	m_delegate = NULL;
    m_DPad = NULL;
    m_circle = NULL;
}

DirectionPad::~DirectionPad(void)
{
    CC_SAFE_RELEASE(m_DPad);
    CC_SAFE_RELEASE(m_circle);
}

DirectionPad* DirectionPad::create(String *fileName, float radius)
{
	DirectionPad *pRet = new DirectionPad();
	if (pRet && pRet->initWithFile(fileName, radius))
	{
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool DirectionPad::initWithFile(String *fileName, float radius)
{
	bool bRet = false;
	do 
	{
        m_DPad = CCSpriteBatchNode::create(fileName->getCString());
		CC_BREAK_IF(m_DPad == NULL);
        m_DPad->retain();
    
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(STEEL_WHEEL_PNG2));
        
		m_radius = radius;
		m_direction = Point(0,0);
		m_isHeld = false;
		//this->scheduleUpdate();

        m_circle = CCSprite::createWithSpriteFrameName(STEEL_WHEEL_CIRCLE_PNG2);
        m_circle->retain();
        addChild(m_circle);
        m_circle->setPosition(convertToNodeSpace(CCSprite::getPosition()));
        
		bRet = true;
	} while (0);

	return bRet;
}

void DirectionPad::onEnterTransitionDidFinish()
{
	Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void DirectionPad::onExit()
{
	Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
}

void DirectionPad::update(float dt)
{
	if (m_isHeld)
	{
		m_delegate->onKeepDirection(m_direction);
	}
}

bool DirectionPad::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point location = pTouch->getLocation();

    Sprite::setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STEEL_WHEEL_PNG1));
	m_circle->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STEEL_WHEEL_CIRCLE_PNG1));
    
    float distance = getPosition().getDistance(location);//ccpLength(ccpSub(location, getPosition()));
     if (distance <= m_radius * 4)
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//if (location.x < winSize.width / 3 
	{
		this->updateDirectionForTouchLocation(location);
		m_isHeld = true;
        setCirclePosition(location);
		//this->setVisible(true);
        //this->setPosition(location);
		return true;
	}
	return false;

}

void DirectionPad::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
	Point location = pTouch->getLocation();
	this->updateDirectionForTouchLocation(location);
    setCirclePosition(location);
}

void DirectionPad::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
	m_direction = Point::ZERO;
	m_isHeld = false;
    
    if(m_delegate != NULL)
    {
      m_delegate->onDirectionEnded();
    }
    
    
    Sprite::setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STEEL_WHEEL_PNG2));
    m_circle->setDisplayFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName(STEEL_WHEEL_CIRCLE_PNG2));
    m_circle->setPosition(convertToNodeSpace(Sprite::getPosition()));
	//this->setVisible(false);
}



void DirectionPad::setCirclePosition(Point location)
{
    float r = Sprite::getContentSize().width/2 ;// 半径
    Point center = getPosition();
    float radians = (location - center).getAngle();
	float degrees = CC_RADIANS_TO_DEGREES(radians);
    
    if (degrees >157.5 || degrees < -157.5)
    {
        degrees = 180;
    }
    
    else
    {
        degrees = int(degrees / 45) * 45;
    }
    

    int x = center.x + r * cos(CC_DEGREES_TO_RADIANS(degrees));
    int y = center.y + r * sin(CC_DEGREES_TO_RADIANS(degrees));

    Point myPos = convertToNodeSpace( Point(x,y));
    m_circle->setPosition(myPos);
}


void DirectionPad::updateDirectionForTouchLocation(Point location)
{
	float radians = (location - getPosition()).getAngle();
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
    
	if (degrees <= 22.5 && degrees >= -22.5) 
	{
		//right
		m_direction = Point(1.0, 0.0);
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		//bottomright
		m_direction = Point(1.0, -1.0);
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		//bottom
		m_direction = Point(0.0, -1.0);
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		//bottomleft
		m_direction = Point(-1.0, -1.0);
    }
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		//left
		m_direction = Point(-1.0, 0.0);
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		//topright
		m_direction = Point(1.0, 1.0);
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		//top
		m_direction = Point(0.0, 1.0); 
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		//topleft
		m_direction = Point(-1.0, 1.0);
	}
    
    if(m_delegate != NULL)
    {
     m_delegate->onDirectionChanged(m_direction);
    }
	 
}
