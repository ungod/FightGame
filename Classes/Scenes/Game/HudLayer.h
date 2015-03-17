#pragma once
#include "cocos2d.h"
#include "Hud/DirectionPad.h"
#include "Skills/SkillControl/SkillHudLayer.h"
#include "Hud/StatusBar.h"

class HudLayer : public cocos2d::Layer
{
public:
	HudLayer(void);
	~HudLayer(void);

	bool init();

	void createHeroBar();
	void createBossBar();
	void setPortalTipsVisible(bool visible);

	CREATE_FUNC(HudLayer);
	CC_SYNTHESIZE(DirectionPad*, m_dPad, DPad);
	CC_SYNTHESIZE(StatusBar*, m_sBar, SBar);
	CC_SYNTHESIZE(StatusBar*, m_bossBar, BossBar);
	CC_SYNTHESIZE(Sprite*, m_goTips, GoTips);
    CC_SYNTHESIZE(SkillHudLayer*, m_skillHudLayer, SkillHudlayer);

    
};
