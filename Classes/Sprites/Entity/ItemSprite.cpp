#include "ItemSprite.h"
#include "Utils/MiscUtils.h"
#include "DataManager.h"


ItemSprite::ItemSprite()
{
}

ItemSprite::~ItemSprite()
{
}

ItemSprite* ItemSprite::createWithAnimationID( int ID, string idleAnim, string disappearAnim )
{
	ItemSprite* pRet = new ItemSprite;

	if (pRet && pRet->initWithAnimation(ID, idleAnim, disappearAnim))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool ItemSprite::initWithAnimation( int ID, string idleAnim, string disappearAnim )
{
	RETURN_FALSE_IF(idleAnim.length() <= 0);
	RETURN_FALSE_IF(!ContactSprite::init());
	
	m_categoryBits = ITEM_CATEGORY;
	m_maskBits = ITEM_MASK_BITS;

	setDataParam();
	setHitSingleMaxNum(INT_MAX);
	setAnimationID(ID);
	setIdleAnimation(idleAnim);
	setDisappearAnimationAnimation(disappearAnim);
	advanceSet();

	if(getIsWithAnimation())
	{
		addChild(getContactAnimateSprite());
	}
	onStarted();

	return true;
}


void ItemSprite::setDataParam()
{
	setBodySize(Size(50, 50));
	setZtolerance(70);
}


void ItemSprite::updatePosition( const Point &position )
{
	float floorBottom = DataManager::getInstance()->getFloorBottom();
	float floorTop = DataManager::getInstance()->getFloorTop();
	float centerToSides = getIsWithAnimation() ? getContactAnimateSprite()->getContentSize().width / 2 : 0;
	float centerToBottom = getIsWithAnimation() ? getContactAnimateSprite()->getContentSize().height /2 : 0;

	float posX = clampf(position.x, centerToSides, DataManager::getInstance()->getMapWidth() - centerToSides);
	float posZ = clampf(position.y, centerToBottom + floorBottom + m_y, floorTop + centerToBottom + m_y);

	ContactSprite::updatePosition(Point(posX, posZ));
}

void ItemSprite::onCollsion( AnimationSprite* pTarget )
{
	onFinished();
}
