#ifndef __PHYSICALOBJECT_H__
#define __PHYSICALOBJECT_H__

#include "b2Body.h"
#include "CollisionData.h"
#include "ObjectSizes.h"
#include "ObjectTypes.h"
#include <string>
#include <memory>

class World;

class PhysicalObject{
	protected:
		World& world;
		b2Body* body;
		bool is_dead;
		int id;
		const std::string& type;
		b2Vec2 last_position;
		bool last_position_sent;
		bool data_updated;
		CollisionData collision_data;

		virtual void createFixtures() = 0;
		virtual void setInitialVelocity();

	public:
		PhysicalObject(World& world, int id, const std::string& type);
		virtual ~PhysicalObject();

		//Inicializa el cuerpo del objeto
		void initializeBody(b2Body* body);

		//Destruye el cuerpo del objeto
		void destroyBody();

		//Devuelve la posicion del objeto
		b2Vec2 getPosition();

		//Devuelve el cuerpo del objeto
		b2Body* getBody();

		//Devuelve true si el objeto se esta moviendo
		virtual bool isMoving();

		//Devuelve true si el objeto esta activo
		virtual bool isActive();

		//Devuelve true si el objeto esta muerto
		virtual bool isDead();

		//Devuelve true si el objeto es afectado por el viento
		virtual bool isWindAffected();

		//Mata al objeto
		void kill();

		int getId();

		//Devuelve el tipo del objeto
		const std::string& getType();

		virtual void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) = 0;

		//Colisiona con otro objeto
		virtual void collideWithSomething(CollisionData *other);

};

typedef std::shared_ptr<PhysicalObject> physical_object_ptr;

#endif
