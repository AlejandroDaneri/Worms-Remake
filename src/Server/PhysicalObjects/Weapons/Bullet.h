#ifndef __BULLET_H__
#define __BULLET_H__

#include "Worm.h"
#include "PhysicalObject.h"

class Bullet: public PhysicalObject{
	private:
		int damage;
		int radius;
		b2Vec2 epicenter;

	protected:
		void createFixtures() override;
		void setInitialVelocity() override;

	public:

		Bullet(int damage, int radius = 0, b2Vec2 epicenter);
		~Bullet();

		void collide_with_something(CollisionData* other) override;
};

#endif
