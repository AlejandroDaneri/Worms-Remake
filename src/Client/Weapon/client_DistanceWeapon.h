#ifndef __CLIENTDISTANCEWEAPON_H__
#define __CLIENTDISTANCEWEAPON_H__

#include "client_Weapon.h"

class DistanceWeapon: public Weapon{
	public:
		DistanceWeapon(std::string name, int ammo, int damage, int radius);
		~DistanceWeapon() {}
		
		bool hasVariablePower() override;
};

#endif
