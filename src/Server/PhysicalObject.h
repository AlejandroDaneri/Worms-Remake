#ifndef __PHYSICALOBJECT_H__
#define __PHYSICALOBJECT_H__

#include "World.h"
#include "b2Body.h"

class World;

class PhysicalObject{
	private:
		World& world;

	protected:
		b2Body* body;

		virtual b2BodyDef* getBodyDef(const b2Vec2& pos) = 0;
		virtual void createFixtures() = 0;

	public:
		PhysicalObject(World& world);
		virtual ~PhysicalObject();

		void addToWorld(const b2Vec2& pos);
		b2Vec2 getPosition();
		b2Body* getBody();

};


#endif