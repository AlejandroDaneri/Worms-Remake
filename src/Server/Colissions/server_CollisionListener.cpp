#include "CollisionListener.h"
#include "PhysicalObject.h"
#include "Worm.h"

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
	}

	b2WorldManifold manifold;
	contact->GetWorldManifold(&manifold);
	b2Vec2 normal = manifold.normal;

	if (dataA->getType() == TYPE_WORM && dataB->getType() == TYPE_GIRDER && normal.y > 0){
		return; //gusano colisiona por abajo de la viga
	}

	if (dataB->getType() == TYPE_WORM && dataA->getType() == TYPE_GIRDER && normal.y < 0){
		return; //gusano colisiona por abajo de la viga
	}

	if (dataA->getType() == TYPE_WORM){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == TYPE_WORM){
		dataB->getObject()->collide_with_something(dataA);
	}
}

void CollisionListener::EndContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getType() == TYPE_WORM && dataB->getType() == TYPE_GIRDER){
		((Worm*)dataA->getObject())->end_collission_girder();
	} else if (dataB->getType() == TYPE_WORM && dataA->getType() == TYPE_GIRDER){
		((Worm*)dataB->getObject())->end_collission_girder();
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
