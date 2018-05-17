#include "CollisionListener.h"
#include "PhysicalObject.h"

CollisionListener::CollisionListener(){}

CollisionListener::~CollisionListener(){}

void CollisionListener::BeginContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getObject()->isDead() || dataB->getObject()->isDead()){
		return;
	}

	if (dataA->getType() == TYPE_WEAPON){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == TYPE_WEAPON){
		dataB->getObject()->collide_with_something(dataA);
	} else if (dataA->getType() == TYPE_WORM){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == TYPE_WORM){
		dataB->getObject()->collide_with_something(dataA);
	}
}

bool CollisionListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB){
	CollisionData* dataA = (CollisionData*)fixtureA->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)fixtureB->GetBody()->GetUserData();

	return dataA->getType() != TYPE_WORM || dataB->getType() != TYPE_WORM;
}
