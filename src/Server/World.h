#ifndef __WORLD_H__
#define __WORLD_H__

#include "Thread.h"
#include "b2World.h"
#include "b2Body.h"
#include "PhysicalObject.h"
#include <mutex>

class PhysicalObject;

class World: public Thread{
	private:
		b2World world;
		std::mutex mutex;

		void initialize();

	public:
		World(const b2Vec2& gravity);
		~World();

		void run() override;

		b2Body* addObject(const b2BodyDef* def);

		void removeObject(PhysicalObject& object);

};


#endif
