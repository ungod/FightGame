
#pragma once

#include "Box2d/Box2D.h"
#include <list>
using std::list;

class MyContact
{
public:
    b2Fixture *fixtureA;
	b2Fixture *fixtureB;
	
    bool operator==(const MyContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

//box2d中的碰撞监听

class MyContactListener : public b2ContactListener
{
public:
    MyContactListener();
    ~MyContactListener();
	//! Callbacks for derived classes.
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse);
public:
    
	std::list<MyContact> contact_list;
};
