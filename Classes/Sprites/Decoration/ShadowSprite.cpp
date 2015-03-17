#include "ShadowSprite.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;


ShadowSprite::ShadowSprite()
{
    m_relativePos = Point::ZERO;
}

ShadowSprite::~ShadowSprite(void)
{

    
}


ShadowSprite* ShadowSprite::createWithTexture(Texture2D *texture)
{
    ShadowSprite *sprite = new ShadowSprite();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

ShadowSprite* ShadowSprite::createWithTexture(Texture2D *texture, const Rect& rect)
{
    ShadowSprite *sprite = new ShadowSprite();
    if (sprite && sprite->initWithTexture(texture, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

ShadowSprite* ShadowSprite::create(const char *filename)
{
    ShadowSprite *sprite = new ShadowSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

ShadowSprite* ShadowSprite::create(const char *filename, const Rect& rect)
{
    ShadowSprite *sprite = new ShadowSprite();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

ShadowSprite* ShadowSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    ShadowSprite *sprite = new ShadowSprite();
    if (pSpriteFrame && sprite && sprite->initWithSpriteFrame(pSpriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

ShadowSprite* ShadowSprite::createWithSpriteFrameName(const char *spriteFrameName)
{
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName);
    CCASSERT(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

ShadowSprite* ShadowSprite::create()
{
    ShadowSprite *pSprite = new ShadowSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}






