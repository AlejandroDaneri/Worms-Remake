#ifndef __CLIENTBAZOOKA_H__
#define __CLIENTBAZOOKA_H__

#include "client_DistanceWeapon.h"
#include "client_Weapons_defs.h"

class Bazooka: public DistanceWeapon{
	public:
		Bazooka(int ammo = INFINITE);
		~Bazooka();
};

#endif
