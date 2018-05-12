#ifndef __CLIENTREDGRENADE_H__
#define __CLIENTREDGRENADE_H__

#include "client_DistanceWeapon.h"

class RedGrenade: public DistanceWeapon {
	public:
		RedGrenade(int ammo);
		~RedGrenade();
};

#endif
