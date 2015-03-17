#pragma once
#include "cocos2d.h"

USING_NS_CC;




class ShadowSprite : public Sprite
{
public:
	ShadowSprite();
	~ShadowSprite(void);
   
   static ShadowSprite* create();
   static ShadowSprite* create(const char *filename);
   static ShadowSprite* create(const char *filename, const Rect& rect);
   static ShadowSprite* createWithTexture(Texture2D *texture);
   static ShadowSprite* createWithTexture(Texture2D *texture, const Rect& rect);
   static ShadowSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
   static ShadowSprite* createWithSpriteFrameName(const char *spriteFrameName);


    CC_SYNTHESIZE(Point, m_relativePos, RelativePos);//相对于角色底部中心的位置
    CC_SYNTHESIZE(Size, m_expectSize, ExpectSize);//期望尺寸
};
