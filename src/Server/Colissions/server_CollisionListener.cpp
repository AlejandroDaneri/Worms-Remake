#include "CollisionListener.h"
#include "PhysicalObject.h"

CollisionListener::CollisionListener(){}

CollisionListener::~CollisionListener(){}

void CollisionListener::BeginContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getType() == "Weapon"){
		///////////////////////////////////////////////////
	} else if (dataB->getType() == "Weapon"){
		///////////////////////////////////////////////////
	} else if (dataA->getType() == "Bullet"){
		////////////////////////////////////////////////////
	} else if (dataB->getType() == "Bullet"){
		///////////////////////////////////////////////////
	} else if (dataA->getType() == "Worm"){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == "Worm"){
		dataB->getObject()->collide_with_something(dataA);
	}
}