#ifndef __CLIENTGREENGRENADE_H__
#define __CLIENTGREENGRENADE_H__

#include "client_DistanceWeapon.h"

class GreenGrenade: public DistanceWeapon {
	public:
		GreenGrenade(int ammo);
		~GreenGrenade();
};

#endif
