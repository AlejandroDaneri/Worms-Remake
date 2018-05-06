#ifndef __PHYSICALOBJECT_H__
#define __PHYSICALOBJECT_H__

#include "World.h"
#include "b2Body.h"
#include <memory>

class World;

class PhysicalObject{
	private:
		World& world;

	protected:
		b2Body* body;
		bool is_dead;

		virtual void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) = 0;
		virtual void createFixtures() = 0;

	public:
		PhysicalObject(World& world);
		virtual ~PhysicalObject();

		void addToWorld(const b2Vec2& pos);
		b2Vec2 getPosition();
		b2Body* getBody();
		bool isMoving();
		bool isDead();

		//virtual void collide_with_something(CollisionData other) = 0;

};

typedef std::unique_ptr<PhysicalObject> physical_object_ptr;

#endif
