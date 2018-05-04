#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <memory>
#include "AttackRadius.h"
#include "Position.h"
#include "Direction.h"

class Weapon;
typedef std::unique_ptr<Weapon> weapon_ptr;

class Weapon{

	protected:
		int munitions;
		AttackRadius radius;

		virtual Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power) = 0;

	public:
		Weapon(int munitions, int radius, int damage);
		~Weapon();

		virtual bool hasScope() = 0;
		virtual bool hasVariablePower() = 0;
		virtual bool isTimed() = 0;
		virtual bool isSelfDirected() = 0;

		virtual void shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time);

		virtual void shoot(const Position& pos);

};

#endif
