#ifndef __CLIENTHOLYGRENADE_H__
#define __CLIENTHOLYGRENADE_H__

#include "DistanceWeapon.h"

class HolyGrenade: public DistanceWeapon {
	public:
		HolyGrenade(int ammo);
		~HolyGrenade();
		HolyGrenade(HolyGrenade&& other);
};

#endif
