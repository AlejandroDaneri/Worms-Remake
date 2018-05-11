#ifndef __CLIENTDISTANCEWEAPON_H__
#define __CLIENTDISTANCEWEAPON_H__

#include "client_Weapon.h"

class DistanceWeapon: public Weapon{
	protected:
		int time;

	public:
		DistanceWeapon(std::string name, int ammo, int damage, int radius, int time = -1);
		~DistanceWeapon() {}
		
		bool hasVariablePower() override;
		void changeTime(int time) override;
		int getTime() override;
};

#endif
