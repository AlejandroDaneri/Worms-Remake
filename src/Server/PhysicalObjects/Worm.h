#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"
#include "GameParameters.h"
#include "Weapon.h"

class Worm: public PhysicalObject{	
	private:
		int life;
		char dir;
		GameParameters& parameters;
		physical_object_ptr weapon;


	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, int id, GameParameters& parameters);
		~Worm();

		int getLife();
		char getDir();

		void move(char action);

		void changeWeapon(const std::string& weapon);

		void shoot(int angle, int power, int time);

		void shoot(b2Vec2 pos);

		void collide_with_something(CollisionData* other) override;

		void reduce_life(int damage);
};

typedef std::shared_ptr<Worm> worm_ptr;

#endif
