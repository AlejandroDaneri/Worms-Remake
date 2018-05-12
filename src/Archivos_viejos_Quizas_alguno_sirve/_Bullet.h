#ifndef __BULLET_H__
#define __BULLET_H__

#include "Worm.h"
#include "PhysicalObject.h"

class Bullet: public PhysicalObject{
	private:
		int angle;
		int damage;
		int radius;
		b2Vec2 epicenter;

	protected:
		void createFixtures() override;
		void setInitialVelocity() override;

	public:

		Bullet(World& world, int angle, int damage, int radius, b2Vec2 epicenter);
		~Bullet();

		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;

		bool isDead() override;

		void collide_with_something(CollisionData* other) override;

		b2Vec2 getEpicenter();
};

#endif
