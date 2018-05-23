#ifndef __CLIENTMORTAR_H__
#define __CLIENTMORTAR_H__

#include "DistanceWeapon.h"


class Mortar: public DistanceWeapon {
	public:
		Mortar(int ammo);
		~Mortar();
		Mortar(Mortar&& other);
};

#endif
