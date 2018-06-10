#ifndef __SERVERFRAGMENT_H__
#define __SERVERFRAGMENT_H__

#include "Weapon.h"

class Fragment: public Weapon{
	private:
		b2Vec2 shoot_position;

	public:
		Fragment(World& world, GameParameters& parameters, int damage, int radius);
		~Fragment();

		void setShootPosition(b2Vec2 pos);
		b2Vec2 getShootPosition();

		void shoot(int angle);
};

#endif
