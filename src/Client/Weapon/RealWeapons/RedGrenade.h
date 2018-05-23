#ifndef __CLIENTREDGRENADE_H__
#define __CLIENTREDGRENADE_H__

#include "DistanceWeapon.h"

class RedGrenade: public DistanceWeapon {
	public:
		RedGrenade(int ammo);
		~RedGrenade();
		RedGrenade(RedGrenade&& other);
};

#endif
