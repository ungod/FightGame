#include "AiPlayer.h"
#include "Sprites/RoleFilter/RoleFilter.h"
#include "DataManager.h"
#include "EntitiesManager.h"
#include "Skills/Actions/SkillMoveBy.h"
#include "DataInfo/MonsterProp.h"

static const float g_tickRate = 0.5f;

AiPlayer::AiPlayer()
{
	m_pMonsterHalo = NULL;
	m_pBossNameSprite = NULL;
	m_pDieEffect = NULL;
}


AiPlayer::~AiPlayer()
{
    unschedule(schedule_selector(AiPlayer::update));
}


 AiPlayer* AiPlayer::create(SimpleAnimation* pBaseSprite)
{
    AiPlayer* pRet = new AiPlayer();
    if(pRet && pRet->initWithAnimateAction(pBaseSprite))
    {
       pRet->autorelease();
    }
    return pRet;
}


void AiPlayer::attack()
{
	CCAssert(m_animationSprite != NULL, "m_animationSprite  cannot be NULL");

	if(!getActive())
		return;

	if (m_actionState == kActionStateIdle ||  m_actionState == kActionStateWalk)//攻击动作完成才可以继续攻击
	{
		m_animationSprite->playAnimation(SPRITE_ATTACK);
		m_actionState = kActionStateAttack;

		do {
			CC_BREAK_IF(getSkillListManager() == NULL);
			Skill* attackSkill = getSkillListManager()->getSkillAtIndex(0);

			CC_BREAK_IF(attackSkill == NULL);
			runSkill(attackSkill);
		} while (0);

	}
    
}




bool AiPlayer::initWithAnimateAction(SimpleAnimation* pAnimationSprite)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!AnimationSprite::initWithAnimateAction(pAnimationSprite));
        setRoleFilter(eRoleFilterMonster);
		setTag(MONSTER_TAG);
		schedule(schedule_selector(AiPlayer::updateAi), g_tickRate);

        bRet = true;
    } while (0);


    return bRet;
}

void AiPlayer::updateAi(float dt)
{
	EntitiesManager* emgr = DataManager::getInstance()->getEntitiesManager();
	Array* roleArray = emgr->getRoleArray();
	Array* targetArray = emgr->getRoleArray(RoleFilter::getOpponentEnum(getRoleFilter()));

	AiModule::tick(dt, targetArray, roleArray);
}

bool AiPlayer::startAiModule()
{
	return AiModule::init(((MonsterProp*)m_roleProp)->getAiModule(), this);
}

void AiPlayer::knockout()
{
	AnimationSprite::knockout();

	if (m_pDieEffect)
	{
		//TODO:播放死亡特效，目前还没有资源
		m_pDieEffect->playAnimation("die");
	}
}

void AiPlayer::initAccessory()
{
	MonsterProp* prop = (MonsterProp*)getRoleProperty();
	if (prop->getType() == ELITE_MONSTER)
	{
		//TODO:添加光环资源，目前还没有资源
		//m_pMonsterHalo = Sprite::createWithTexture();
	}
	else if (prop->getType() == BOSS_MONSTER)
	{
		//TODO:添加光环资源，BOSS名字，死亡效果，目前还没有资源
		//m_pMonsterHalo = Sprite::createWithTexture();
		//m_pBossNameSprite = Sprite::createWithTexture()
		//m_pDieEffect = SimpleAnimation::create()
	}
}

