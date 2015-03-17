#pragma once
#include "cocos2d.h"
#include "Includes/Resources.h"


USING_NS_CC;


class NoteSprite : public Sprite
{
public:
	NoteSprite();
	~NoteSprite();

	static NoteSprite* createWithSpriteFrameName(const char *spriteFrameName);
	static NoteSprite* createNum(int num);

	void initNum(int num);
	void onEnd();

private:
	Sprite* m_numberSprites[10];
};
