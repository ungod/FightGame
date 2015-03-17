#pragma once
#include "ItemSprite.h"

class PortalSprite : public ItemSprite
{
public:
	PortalSprite();
	~PortalSprite();

	static PortalSprite* createWithID(int ID);

	virtual void setDataParam();
	virtual void onCollsion(AnimationSprite* pTarget);
    
    CC_SYNTHESIZE(int, m_nextMapID, NextMapID);
	CC_SYNTHESIZE(bool, m_collsionManual, CollsionManual);
};