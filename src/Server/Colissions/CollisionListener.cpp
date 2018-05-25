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
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == TYPE_WEAPON){
		dataB->getObject()->collide_with_something(dataA);
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
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == TYPE_WORM){
		dataB->getObject()->collide_with_something(dataA);
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
		bool friction = ((Girder*)dataB->getObject())->has_friction();
		((Worm*)dataA->getObject())->end_collission_girder(friction);
	} else if (dataB->getType() == TYPE_WORM && dataA->getType() == TYPE_GIRDER){
		bool friction = ((Girder*)dataA->getObject())->has_friction();
		((Worm*)dataB->getObject())->end_collission_girder(friction);
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