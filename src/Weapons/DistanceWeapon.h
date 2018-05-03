#ifndef __DISTANCEWEAPON_H__
#define __DISTANCEWEAPON_H__

#include "Weapon.h"

class DistanceWeapon: public Weapon{
	protected:
		Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power);

	public:
		DistanceWeapon(int munitions, int radius, int damage);
		~DistanceWeapon();

		bool hasScope();
		bool hasVariablePower();
		bool isSelfDirected();

};

#endif
