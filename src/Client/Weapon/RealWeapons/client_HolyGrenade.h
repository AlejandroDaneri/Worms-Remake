#ifndef __CLIENTHOLYGRENADE_H__
#define __CLIENTHOLYGRENADE_H__

#include "client_DistanceWeapon.h"

class HolyGrenade: public DistanceWeapon {
	public:
		HolyGrenade(int ammo);
		~HolyGrenade();
};

#endif
