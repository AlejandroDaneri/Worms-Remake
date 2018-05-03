#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <memory>
#include "AtackRadius.h"
#include "Position.h"

class Weapon;
typedef std::unique_ptr<Weapon> weapon_ptr;

class Weapon{
	private:
		bool scope;
		bool variable_power;
		bool timed;
		AtackRadius radius;

	public:
		Weapon(bool scope, bool variable_power, bool timed, int radius, int damage);
		~Weapon();

		bool hasScope();
		bool hasVaraiblePower();
		bool isTimed();

		virtual void shoot(int angle, int power, int time);

		virtual void shoot(const Position& pos);

};

#endif
