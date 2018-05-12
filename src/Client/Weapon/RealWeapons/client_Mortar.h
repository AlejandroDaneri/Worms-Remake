#ifndef __CLIENTMORTAR_H__
#define __CLIENTMORTAR_H__

#include "client_DistanceWeapon.h"


class Mortar: public DistanceWeapon {
	public:
		Mortar(int ammo);
		~Mortar();
};

#endif
