#ifndef __FRAGMENTABLEWEAPON_H__
#define __FRAGMENTABLEWEAPON_H__

#include "Weapon.h"

class FragmentableWeapon: public Weapon{
	protected:
		int fragments;

	public:

		FragmentableWeapon(World& world, GameParameters& parameters, int damage, int fragments, int radius = 0, int ricochets = 0);
		virtual ~FragmentableWeapon();

		void explode();
};

#endif
