#ifndef __SERVERFRAGMENT_H__
#define __SERVERFRAGMENT_H__

#include "Weapon.h"

class Fragment: public Weapon{
	private:
		b2Vec2 shoot_position;

	public:

		Fragment(World& world, GameParameters& parameters, int damage, int radius);
		~Fragment();

		void set_shoot_position(b2Vec2 pos);
		b2Vec2 get_shoot_position();

		void shoot(int angle, int time);

};

#endif