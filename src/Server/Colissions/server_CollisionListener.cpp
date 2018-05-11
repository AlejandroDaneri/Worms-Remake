#include "CollisionListener.h"
#include "PhysicalObject.h"

CollisionListener::CollisionListener(){}

CollisionListener::~CollisionListener(){}

void CollisionListener::BeginContact(b2Contact* contact){
	CollisionData* dataA = (CollisionData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionData* dataB = (CollisionData*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (dataA->getType() == "Weapon"){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == "Weapon"){
		dataB->getObject()->collide_with_something(dataA);
	} else if (dataA->getType() == "Bullet"){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == "Bullet"){
		dataB->getObject()->collide_with_something(dataA);
	} else if (dataA->getType() == "Worm"){
		dataA->getObject()->collide_with_something(dataB);
	} else if (dataB->getType() == "Worm"){
		dataB->getObject()->collide_with_something(dataA);
	}
}