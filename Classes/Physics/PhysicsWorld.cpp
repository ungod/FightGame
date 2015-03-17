#include "PhysicsWorld.h"
#include "DataManager.h"
#include "ContactHandler.h"
#include "Sprites/Physics/ContactSprite.h"
#include "Sprites/Entity/SkillContactSprite.h"
#include "Config.h"

class DataManager;
class ContactSprite;

PhysicsWorld *PhysicsWorld::create()
{
    PhysicsWorld *pPhysicsWorld;
    pPhysicsWorld = new PhysicsWorld();
    
    if(pPhysicsWorld)
    {
        pPhysicsWorld->initWorld();
    }
    
    return pPhysicsWorld;
}


PhysicsWorld::PhysicsWorld()
: m_pWorld(NULL)
,m_pContactListener(NULL)
, m_pDebugDraw(NULL)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    CC_SAFE_DELETE(m_pDebugDraw);
    CC_SAFE_DELETE(m_pContactListener);
    CC_SAFE_DELETE(m_pWorld);
    
    log("Delete PhysicsWorld");
    
}


bool PhysicsWorld::initWorld()
{
    b2Vec2 noGravity(0, 0);
    
    m_pWorld = new b2World(noGravity);
    m_pWorld->SetAllowSleeping(true);
    
    m_pContactListener = new MyContactListener();
    m_pWorld->SetContactListener(m_pContactListener);
    
    Size groundSize = Size(DataManager::getInstance()->getMapWidth(),DataManager::getInstance()->getFloorTop());
    float floorBottom = DataManager::getInstance()->getFloorBottom()/ PTM_RATIO;
    float floorTop = DataManager::getInstance()->getFloorTop()/ PTM_RATIO;
    
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
	m_groundBody = m_pWorld->CreateBody(&groundBodyDef);
    
    
    b2FixtureDef groundFixtureDef;
    groundBodyDef.type = b2_staticBody;
    groundFixtureDef.filter.categoryBits = GROUND_CATEGORY;
    groundFixtureDef.filter.maskBits = GROUND_MASK_BITS;
  
    
   	// Define the ground box shape.
	b2EdgeShape groundShape;
	
    // top
	groundShape.Set(b2Vec2(0,floorTop), b2Vec2(groundSize.width/PTM_RATIO,floorTop));
	groundFixtureDef.shape = &groundShape;
    m_groundBody->CreateFixture(&groundFixtureDef);
    // bottom
	groundShape.Set(b2Vec2(0,floorBottom),b2Vec2(groundSize.width/PTM_RATIO,floorBottom));
	groundFixtureDef.shape = &groundShape;
    m_groundBody->CreateFixture(&groundFixtureDef);

	
    // left
	groundShape.Set(b2Vec2(0,floorBottom), b2Vec2(0,groundSize.height / PTM_RATIO));
	groundFixtureDef.shape = &groundShape;
    m_groundBody->CreateFixture(&groundFixtureDef);
	
	// right
	groundShape.Set(b2Vec2(groundSize.width/PTM_RATIO,groundSize.height/PTM_RATIO), b2Vec2(groundSize.width/PTM_RATIO,0));
	groundFixtureDef.shape = &groundShape;
    m_groundBody->CreateFixture(&groundFixtureDef);
   
    
	if (Config::PhyDebug)
	{
		m_pDebugDraw = new extension::armature::GLESDebugDraw( PTM_RATIO );
		m_pWorld->SetDebugDraw(m_pDebugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		// flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_pDebugDraw->SetFlags(flags);
	}
    
    return true;
}

b2World *PhysicsWorld::getWorld()
{
    return m_pWorld;
}

void PhysicsWorld::update(float dt)
{
    int velocityIterations = 8;
	int positionIterations = 8;
    m_pWorld->Step(dt, velocityIterations, positionIterations);
   
    ContactHandler contactHandler;
    
    for (std::list<MyContact>::iterator it = m_pContactListener->contact_list.begin(); it != m_pContactListener->contact_list.end(); ++it)
    {
        MyContact &contact = *it;
        
        b2Body *b2a = contact.fixtureA->GetBody();
        b2Body *b2b = contact.fixtureB->GetBody();

        if(b2a->GetUserData() != NULL && b2b->GetUserData() != NULL)
        {
            Node* nodeA = (Node*)b2a->GetUserData();
            Node* nodeB = (Node*)b2b->GetUserData();
            ContactSprite* contactSprite = NULL;
            AnimationSprite* target = NULL;
			int tagA = nodeA->getTag();
			int tagB = nodeB->getTag();
            
            if(tagA != kActionTagInvalid && tagA & CONTACT_TAG )//分离目标和碰撞体
            {
                contactSprite = (ContactSprite*) nodeA;
                target = dynamic_cast<AnimationSprite*>(nodeB);
            }
            
            if(tagB != kActionTagInvalid && tagB & CONTACT_TAG )
            {
                contactSprite = (ContactSprite*) nodeB;
                target = dynamic_cast<AnimationSprite*>(nodeA);
            }
            
            if( contactSprite != NULL  && target != NULL)
            {
                bool collisionFlag = contactSprite->checkCollision(target);//检测是否击中目标
                if(collisionFlag)
                {
					if (contactSprite->getTag() == SKILL_TAG)
					{
						SkillContactSprite* skillSprite = (SkillContactSprite*)contactSprite;
						Skill* skill = skillSprite->getSkillParent();//获取技能实例
						contactHandler.addSkillList(skillSprite, target);
						contactHandler.addSkillMap(skillSprite, skill);
					}
					else
					{
						contactHandler.addContactList(contactSprite, target);
					}
                }
            }
        }
        
    }
    
    
    contactHandler.handle();//处理数据
    
}

void PhysicsWorld::drawDebug()
{
    
	if (Config::PhyDebug)
	{
		GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );

		kmGLPushMatrix();
		m_pWorld->DrawDebugData();

		kmGLPopMatrix();
	}
}




