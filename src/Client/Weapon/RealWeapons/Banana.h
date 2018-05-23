#ifndef __CLIENTBANANA_H__
#define __CLIENTBANANA_H__

#include "DistanceWeapon.h"

class Banana: public DistanceWeapon {
	public:
		Banana(int ammo);
		~Banana();
		Banana(Banana&& other);
};

#endif
