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
		bool last_position_sended;
		CollisionData collision_data;

		virtual void createFixtures() = 0;
		virtual void setInitialVelocity();

	public:
		PhysicalObject(World& world, int id, const std::string& type);
		virtual ~PhysicalObject();

		void initializeBody(b2Body* body);
		void destroyBody();
		b2Vec2 getPosition();
		b2Body* getBody();
		virtual bool isMoving();
		virtual bool isActive();
		virtual bool isDead();
		virtual bool isWindAffected();
		int getId();
		const std::string& getType();

		virtual void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) = 0;

		virtual void collide_with_something(CollisionData* other);

};

typedef std::shared_ptr<PhysicalObject> physical_object_ptr;

#endif
