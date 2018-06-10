#include "CollisionListener.h"
#include "PhysicalObject.h"
#include "Worm.h"
#include "Girder.h"

CollisionListener::CollisionListener(){}

CollisionListener::~CollisionListener(){}

void CollisionListener::BeginContact(b2Contact* contact){
	CollisionData* dataA = 
				(CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = 
				(CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getObject()->isDead() || dataB->getObject()->isDead()){
		return;
	}

	if (dataA->getType() == TYPE_WEAPON){
		if (dataB->getType() == TYPE_WORM){
			int shooter_id = ((Weapon*)dataA->getObject())->getShooterId();
			int worm_id = dataB->getObject()->getId();
			if (shooter_id == worm_id){
				return;
			}
		}
		dataA->getObject()->collideWithSomething(dataB);
	} else if (dataB->getType() == TYPE_WEAPON){
		if (dataA->getType() == TYPE_WORM){
			int shooter_id = ((Weapon*)dataB->getObject())->getShooterId();
			int worm_id = dataA->getObject()->getId();
			if (shooter_id == worm_id){
				return;
			}
		}
		dataB->getObject()->collideWithSomething(dataA);
	}

	if (dataA->getType() == TYPE_WORM && contact->GetFixtureA()->IsSensor() && 
			(dataB->getType() == TYPE_GIRDER || dataB->getType() == TYPE_BORDER)){
		dataA->getObject()->collideWithSomething(dataB);
		
	} else if (dataB->getType() == TYPE_WORM &&
				contact->GetFixtureB()->IsSensor() && 
				(dataA->getType() == TYPE_GIRDER || dataA->getType() == TYPE_BORDER)){
		dataB->getObject()->collideWithSomething(dataA);
	}
}

void CollisionListener::EndContact(b2Contact* contact){
	CollisionData* dataA = 
				(CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = 
				(CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getType() == TYPE_WORM &&
			contact->GetFixtureA()->IsSensor() && dataB->getType() == TYPE_GIRDER){
		bool friction = ((Girder *) dataB->getObject())->hasFriction();
		((Worm *) dataA->getObject())->endCollissionGirder(friction);
	} else if (dataB->getType() == TYPE_WORM &&
				contact->GetFixtureB()->IsSensor() && dataA->getType() == TYPE_GIRDER){
		bool friction = ((Girder *) dataA->getObject())->hasFriction();
		((Worm *) dataB->getObject())->endCollissionGirder(friction);
	}

	if (dataA->getType() == TYPE_WEAPON){
		((Weapon*)dataA->getObject())->removeShooterId();
	}
	if (dataB->getType() == TYPE_WEAPON){
		((Weapon*)dataB->getObject())->removeShooterId();
	}
}

bool CollisionListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB){
	CollisionData* dataA = (CollisionData*)fixtureA->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)fixtureB->GetBody()->GetUserData();

	if (dataA->getType() == TYPE_WORM && dataB->getType() == TYPE_WORM){
		return false;
	}
	if (dataA->getType() == TYPE_WEAPON && dataB->getType() == TYPE_WEAPON){
		return false;
	}
	return true;
}
