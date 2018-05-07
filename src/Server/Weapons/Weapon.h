#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Worm.h"
#include "PhysicalObject.h"
#include "Explosion.h"

class Weapon: public PhysicalObject{
	protected:
		Explosion explosion;

		void createFixtures();
		void setInitialVelocity();

	private:
		int default_velocity;
		bool waiting_to_explode;
		int time_to_explode;
		int angle;
		int power;

	public:
		Weapon(World& world, int id, int radius, int damage, int default_velocity);
		~Weapon();

		virtual void shoot(int angle = -1, int power = -1, int time = -1);

		bool isMoving() override;

		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;

};

#endif
