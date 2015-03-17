#include "NPCSprite.h"
#include "Sqlite/SqliteResolver.h"
#include "Utils/MiscUtils.h"

NPCSprite::NPCSprite()
{
	m_target = NULL;
}

NPCSprite::~NPCSprite()
{
}

NPCSprite* NPCSprite::create(int ID)
{
	NPCSprite* sp = new NPCSprite;

	if (sp && sp->initWithID(ID))
	{
		sp->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sp);
	}

	return sp;
}


bool NPCSprite::initWithID( int ID )
{
	SqliteResolver* npcSrl = SqliteResolver::create(TABLE_NPC, ID);
	RETURN_FALSE_IF(!npcSrl);

	SqliteResolver* roleSrl = SqliteResolver::create(TABLE_ROLES, npcSrl->getInt("RoleID"));
	RETURN_FALSE_IF(!roleSrl);

	SqliteResolver* animateResolver = SqliteResolver::create(TABLE_ANIMATIONS, roleSrl->getInt("AnimationID"));
	RETURN_FALSE_IF(!animateResolver);

	char* animationName = animateResolver->loadSimpleSprite();
	RETURN_FALSE_IF(!animationName);

	RETURN_FALSE_IF(!initWithAnimateAction(SimpleAnimation::create(animationName)));

	string shadowFile = roleSrl->getString("ShadowFile");

	ShadowSprite* shadowSprite = ShadowSprite::create(shadowFile.c_str());
	if(!shadowSprite)
		return true;

	Size size = roleSrl->getSize("ShadowSize");
	Size contentSize = shadowSprite->getContentSize();
	shadowSprite->setExpectSize(size);
	float scaleX = size.width / contentSize.width / SCALE_FACTOR;
	float scaleY = size.height / contentSize.height / SCALE_FACTOR;
	shadowSprite->setScaleX(scaleX);
	shadowSprite->setScaleY(scaleY);

	Point pos = roleSrl->getPoint("ShadowPosition") / SCALE_FACTOR;
	shadowSprite->setRelativePos(pos);
	setShadow(shadowSprite);
	addChild(shadowSprite);

	Size bodySize = roleSrl->getSize("BodySize");
	setCenterToBottom((bodySize.height)/ 2);
	setCenterToSides((bodySize.width)/ 2);

	shadowSprite->setPosition( Point(shadowSprite->getRelativePos().x,
		-(bodySize.height / 2) + shadowSprite->getRelativePos().y) / SCALE_FACTOR);

	shadowSprite->setOpacity(210);

	m_label = LabelTTF::create("Talk", "Times New Roman", 20);
	m_label->setPosition(Point(0, 50));
	m_label->setVisible(false);
	addChild(m_label);

	return true;
}

void NPCSprite::update( float delta )
{
	AnimationSprite::update(delta);

	if (m_target)
	{
		Point p = Point(abs(m_target->getX() - getX()), m_target->getZ() - getZ());
		if (p.x < 50 && p.y < 50)
		{
			m_label->setVisible(true);
		}
		else
		{
			m_label->setVisible(false);
		}
	}
}
