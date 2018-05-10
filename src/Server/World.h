#ifndef __WORLD_H__
#define __WORLD_H__

#include "Thread.h"
#include "b2World.h"
#include "b2Body.h"
#include "PhysicalObject.h"
#include "CollisionListener.h"
#include <mutex>
#include <list>

class PhysicalObject;
typedef std::shared_ptr<PhysicalObject> physical_object_ptr;

class World: public Thread{
	private:
		b2World world;
		std::mutex mutex;
		std::list<physical_object_ptr> objects;
		CollisionListener collision_listener;
		std::list<physical_object_ptr> girders;

		void initialize();
		void removeObject(physical_object_ptr object);

	public:
		World(const b2Vec2& gravity = b2Vec2(0.0f, -10.0));
		~World();

		void run() override;

		void addObject(physical_object_ptr object, const b2Vec2& pos);

		b2Vec2 getObjectPosition(PhysicalObject& object);

		void setLinearVelocity(PhysicalObject& object, b2Vec2& velocity);

		std::list<physical_object_ptr>& getObjectsList();

		std::mutex& getMutex();

};


#endif
