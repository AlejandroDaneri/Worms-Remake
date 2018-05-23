#ifndef __CLIENTGREENGRENADE_H__
#define __CLIENTGREENGRENADE_H__

#include "DistanceWeapon.h"

class GreenGrenade: public DistanceWeapon {
	public:
		GreenGrenade(int ammo);
		~GreenGrenade();
		GreenGrenade(GreenGrenade&& other);
};

#endif
