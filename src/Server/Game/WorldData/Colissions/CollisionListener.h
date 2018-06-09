#ifndef __COLLISIONLISTENER_H__
#define __COLLISIONLISTENER_H__

#include <string>
#include "CollisionData.h"
#include "b2WorldCallbacks.h"
#include "b2Contact.h"
#include <list>

class CollisionListener: public b2ContactListener, public b2ContactFilter{
	public:
		CollisionListener();
		~CollisionListener();

		//Analiza la colision entre dos objetos
		void BeginContact(b2Contact* contact) override;

		//Analiza el fin de colision entre dos objetos
		void EndContact(b2Contact* contact) override;

		//Analiza si dos objetos deben colisionar o no
		bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
};

#endif
