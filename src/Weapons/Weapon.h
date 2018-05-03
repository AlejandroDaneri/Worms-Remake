#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <memory>
#include "AtackRadius.h"
#include "Position.h"
#include "Direction.h"

class Weapon;
typedef std::unique_ptr<Weapon> weapon_ptr;

class Weapon{
	private:
		bool scope;
		bool variable_power;
		bool timed;
		bool self_directed;

	protected:
		AtackRadius radius;

		virtual Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power) = 0;

	public:
		Weapon(bool scope, bool variable_power, bool timed, bool self_directed, int radius, int damage);
		~Weapon();

		bool hasScope();
		bool hasVariablePower();
		bool isTimed();
		bool isSelfDirected();

		virtual void shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time);

		virtual void shoot(const Position& pos);

};

#endif
