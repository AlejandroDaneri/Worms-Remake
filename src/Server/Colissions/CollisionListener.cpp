#include "CollisionListener.h"
#include "PhysicalObject.h"
#include "Worm.h"
#include "Girder.h"

CollisionListener::CollisionListener(){}

CollisionListener::~CollisionListener(){}

void CollisionListener::BeginContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getObject()->isDead() || dataB->getObject()->isDead()){
		return;
	}

	if (dataA->getType() == TYPE_WEAPON){
		dataA->getObject()->collideWithSomething(dataB);
	} else if (dataB->getType() == TYPE_WEAPON){
		dataB->getObject()->collideWithSomething(dataA);
	}

	b2WorldManifold manifold;
	contact->GetWorldManifold(&manifold);
	b2Vec2 collision_point = manifold.points[0];

	if (dataA->getType() == TYPE_WORM && dataB->getType() == TYPE_GIRDER){
		Worm* worm = (Worm*)dataA->getObject();
		if (worm->getPosition().y < collision_point.y){
			//gusano colisiona por abajo de la viga
			this->contacts_disabled.push_back(contact);
			return;
		}
	}

	if (dataB->getType() == TYPE_WORM && dataA->getType() == TYPE_GIRDER){
		Worm* worm = (Worm*)dataB->getObject();
		if (worm->getPosition().y < collision_point.y){
			//gusano colisiona por abajo de la viga
			this->contacts_disabled.push_back(contact);
			return;
		}
	}

	if (dataA->getType() == TYPE_WORM){
		dataA->getObject()->collideWithSomething(dataB);
	} else if (dataB->getType() == TYPE_WORM){
		dataB->getObject()->collideWithSomething(dataA);
	}
}

void CollisionListener::EndContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	for (auto it = this->contacts_disabled.begin(); it != this->contacts_disabled.end(); ++it){
		if (*it == contact){
			this->contacts_disabled.erase(it);
			return;
		}
	}

	if (dataA->getType() == TYPE_WORM && dataB->getType() == TYPE_GIRDER){
		bool friction = ((Girder *) dataB->getObject())->hasFriction();
		((Worm *) dataA->getObject())->endCollissionGirder(friction);
	} else if (dataB->getType() == TYPE_WORM && dataA->getType() == TYPE_GIRDER){
		bool friction = ((Girder *) dataA->getObject())->hasFriction();
		((Worm *) dataB->getObject())->endCollissionGirder(friction);
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
	if (dataA->getType() == TYPE_WEAPON && dataB->getType() == TYPE_WORM){
		int shooter_id = ((Weapon*)dataA->getObject())->getShooterId();
		int worm_id = dataB->getObject()->getId();
		return shooter_id != worm_id;
	}
	if (dataB->getType() == TYPE_WEAPON && dataA->getType() == TYPE_WORM){
		int shooter_id = ((Weapon*)dataB->getObject())->getShooterId();
		int worm_id = dataA->getObject()->getId();
		return shooter_id != worm_id;
	}
	return true;
}
