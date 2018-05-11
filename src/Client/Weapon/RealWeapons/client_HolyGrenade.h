#ifndef __CLIENTHOLYGRENADE_H__
#define __CLIENTHOLYGRENADE_H__

#include "client_DistanceWeapon.h"
#include "client_Weapons_defs.h"

class HolyGrenade: public DistanceWeapon{
	public:
		HolyGrenade(int ammo = HOLY_GRENADE_AMMO);
		~HolyGrenade();
};

#endif
