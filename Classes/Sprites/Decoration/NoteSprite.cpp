#include "NoteSprite.h"


NoteSprite::NoteSprite()
{
}

NoteSprite::~NoteSprite()
{
}

NoteSprite* NoteSprite::createWithSpriteFrameName( const char *spriteFrameName )
{
	NoteSprite* sp = new NoteSprite;

	if (sp && sp->init())
	{
		sp->autorelease();

		Sprite* child = Sprite::createWithSpriteFrameName(spriteFrameName);
		sp->addChild(child);

		Sequence* sq = Sequence::create(MoveTo::create(1, Point(0, 10)),
						CallFunc::create(CC_CALLBACK_0(NoteSprite::onEnd, sp)), NULL);

		child->runAction(sq);


		return sp;
	}
	
	CC_SAFE_DELETE(sp);

	return NULL;
}

NoteSprite* NoteSprite::createNum(int num)
{
	NoteSprite* sp = new NoteSprite;

	if (sp && sp->init())
	{
		sp->autorelease();
		sp->initNum(num);

		return sp;
	}

	CC_SAFE_DELETE(sp);

	return NULL;
}

void NoteSprite::initNum(int num)
{
	int bit = 1, tnum = num;
	while (tnum /= 10) bit++;

	char c[16];
	Sprite* sp;
	Sprite* parent = Sprite::create();
	tnum = num;

	for (int i=bit; i>0; i--)
	{
		sprintf(c, "%d.png", tnum%10);
		sp = Sprite::createWithSpriteFrameName(c);
		sp->setAnchorPoint(Point(0, 0));
		sp->setPosition(Point(sp->getContentSize().width*i, 0));
		parent->addChild(sp);
		tnum /= 10;
	}
	addChild(parent);

	Sequence* sq = Sequence::create(MoveTo::create(1, Point(0, 10)),
		CallFunc::create(CC_CALLBACK_0(NoteSprite::onEnd, this)), NULL);

	parent->runAction(sq);
}

void NoteSprite::onEnd()
{
	getParent()->removeChild(this);
}
