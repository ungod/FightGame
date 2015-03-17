#include "MyContactListener.h"
#include "Box2D/Box2D.h"



//! Callbacks for derived classes.

MyContactListener::MyContactListener()
{


}

MyContactListener::~MyContactListener()
{


}


void MyContactListener::BeginContact(b2Contact *contact)
{
	if (contact)
	{
		MyContact c;
		c.fixtureA = contact->GetFixtureA();
		c.fixtureB = contact->GetFixtureB();
          
		contact_list.push_back(c);

	}
}
void MyContactListener::EndContact(b2Contact *contact)
{
	contact_list.clear();
}
void MyContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}
void MyContactListener::PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}
