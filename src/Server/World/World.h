#ifndef __WORLD_H__
#define __WORLD_H__

#include "Thread.h"
#include "b2World.h"
#include "b2Body.h"
#include "PhysicalObject.h"
#include "CollisionListener.h"
#include "RayCastWeaponExploded.h"
#include "Wind.h"
#include <mutex>
#include <list>

class Weapon;

class World: public Thread{
	private:
		b2World world;
		Wind wind;
		std::mutex mutex;
		CollisionListener collision_listener;
		std::list<physical_object_ptr> objects;
		std::list<physical_object_ptr> girders;
		std::list<physical_object_ptr> fragments_to_add;
		bool is_active;

		void initialize();
		void removeObject(physical_object_ptr object);
		void initializeObject(physical_object_ptr object, b2BodyDef* body_def);
		void add_all_fragments();

	public:
		World(GameParameters& parameters);
		~World();

		void run() override;

		void addObject(physical_object_ptr object, const b2Vec2& pos);

		void addWeaponFragment(physical_object_ptr fragment);

		void removeTimedWeapon(Weapon& weapon);

		b2Vec2 getObjectPosition(PhysicalObject& object);

		void setLinearVelocity(PhysicalObject& object, b2Vec2& velocity);

		bool isActive();

		void update();

		b2Body* getClosestObject(RayCastWeaponExploded* callback, b2Vec2 center, b2Vec2 end);

		std::list<physical_object_ptr>& getObjectsList();
		std::list<physical_object_ptr>& getGirdersList();

		std::mutex& getMutex();

};


#endif
