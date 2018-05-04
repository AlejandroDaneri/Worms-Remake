#ifndef __WORM_H__
#define __WORM_H__

#include "Weapon.h"
#include "Position.h"
#include "Direction.h"

#define WORM_SPEED 0.2///////////////////////////////////////////////////////////////////////////archivo de config

class Worm{
	private:
		Position position;
		int life;
		weapon_ptr weapon;
		dir_ptr dir;

	public:
		Worm(Position position, int life);
		~Worm();

		void set_weapon(weapon_ptr weapon);

		void change_dir();

		void move();

		void jump();

		void roll_back();

		void shoot(int angle, int power, int time);

		void shoot(const Position& pos);

		Position getPosition();

		weapon_ptr getWeapon();

		Worm(Worm&& other);

};

#endif
