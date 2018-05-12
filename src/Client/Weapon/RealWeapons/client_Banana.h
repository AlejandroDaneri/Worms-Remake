#ifndef __CLIENTBANANA_H__
#define __CLIENTBANANA_H__

#include "client_DistanceWeapon.h"

class Banana: public DistanceWeapon {
	public:
		Banana(int ammo);
		~Banana();
};

#endif
