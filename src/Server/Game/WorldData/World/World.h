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
		int sleep_time;
		float time_step;

		//Inicializa el mundo
		void initialize();

		//Remueve un objeto del mundo
		void removeObject(physical_object_ptr object);

		//Inicializa un objeto recien agregado al mundo
		void initializeObject(physical_object_ptr object, b2BodyDef* body_def);

		//Agrega todos los fragmentos de armas al mundo
		void addAllFragments();

	public:
		explicit World(GameParameters& parameters);
		~World();

		void run() override;

		//Agrega el objeto al mundo en la posicion indicada
		void addObject(physical_object_ptr object, const b2Vec2& pos);

		//Agrega un fragmento de arma
		void addWeaponFragment(physical_object_ptr fragment);

		//Elimina una arma del mundo
		void removeTimedWeapon(Weapon& weapon);

		//Setea la velocidad de un objeto
		void setLinearVelocity(PhysicalObject& object, b2Vec2& velocity);

		//Devuelve true si alguno de los objetos esta en movimiento
		bool isActive();

		//Actualiza el mundo
		void update();

		//Devuelve la velocidad del viento
		float getWind() const;

		//Devuelve el objeto mas cercano entre al centro en la direccion end - center
		b2Body* getClosestObject(RayCastWeaponExploded* callback,
										b2Vec2 center, b2Vec2 end);

		//Devuelve la lista de objetos
		std::list<physical_object_ptr>& getObjectsList();

		//Devuelve la lista de vigas
		std::list<physical_object_ptr>& getGirdersList();

		//Devuelve el mutex
		std::mutex& getMutex();
};


#endif
