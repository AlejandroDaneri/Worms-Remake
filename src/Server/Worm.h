#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"

class Worm: public PhysicalObject{	
	private:
		int life;
		char dir;


	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, int id);
		~Worm();

		int getLife();
		char getDir();

		void move(char action);

		void changeWeapon(const std::string& weapon);

		void shoot(int angle, int power, int time);

		void shoot(b2Vec2 pos);

		//virtual void collide_with_something(CollisionData other) = 0;

};

typedef std::shared_ptr<Worm> worm_ptr;

#endif
