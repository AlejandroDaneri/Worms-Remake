#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "PhysicalObject.h"
#include "GameParameters.h"
#include "World.h"
#include "WeaponExplodeTime.h"
#include <string>
#include "WeaponNames.h"

class Worm;

class Weapon: public PhysicalObject{
	protected:
		GameParameters& parameters;
		int damage;
		int radius;
		bool waiting_to_explode;
		int time_to_explode;
		float angle;
		float power;
		WeaponExplodeTime explode_time;

		virtual void createFixtures() override;
		virtual void setInitialVelocity() override;

	public:
		static int weapon_id;

		Weapon(World& world, GameParameters& parameters, int damage, int radius = 0);
		virtual ~Weapon();

		bool isActive() override;

		virtual void shoot(char dir, int angle, int power, int time);

		virtual void shoot(Worm& shooter, b2Vec2 pos);

		virtual void explode();

		virtual void collide_with_something(CollisionData* other) override;

		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;

		virtual const std::string& getName() = 0;

};

#endif
