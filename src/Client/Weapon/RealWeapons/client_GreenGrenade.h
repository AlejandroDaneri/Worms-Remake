#ifndef __CLIENTGREENGRENADE_H__
#define __CLIENTGREENGRENADE_H__

#include "client_DistanceWeapon.h"
#include "client_Weapons_defs.h"

class GreenGrenade: public DistanceWeapon{
	public:
		GreenGrenade(int ammo = INFINITE);
		~GreenGrenade();
};

#endif
