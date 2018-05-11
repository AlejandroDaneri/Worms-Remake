#ifndef __CLIENTBAZOOKA_H__
#define __CLIENTBAZOOKA_H__

#include "client_DistanceWeapon.h"

class Bazooka: public DistanceWeapon{
	public:
		Bazooka(int ammo);
		~Bazooka();
};

#endif
