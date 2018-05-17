#ifndef __COLLISIONLISTENER_H__
#define __COLLISIONLISTENER_H__

#include <string>
#include "CollisionData.h"
#include "b2WorldCallbacks.h"
#include "b2Contact.h"

class CollisionListener: public b2ContactListener, public b2ContactFilter{
	public:
		CollisionListener();
		~CollisionListener();

		void BeginContact(b2Contact* contact) override;

		bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
};

#endif
