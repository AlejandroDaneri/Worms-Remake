#ifndef __CLIENTDISTANCEWEAPON_H__
#define __CLIENTDISTANCEWEAPON_H__

#include "Weapon.h"

class DistanceWeapon: public Weapon{
	public:
		DistanceWeapon(std::string name, int ammo, bool time = false);
		~DistanceWeapon();
		DistanceWeapon(DistanceWeapon&& other);
		
		bool hasVariablePower() const override;
};

#endif
