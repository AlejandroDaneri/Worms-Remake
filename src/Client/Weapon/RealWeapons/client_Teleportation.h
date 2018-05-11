#ifndef __CLIENTTELEPORTATION_H__
#define __CLIENTTELEPORTATION_H__

#include "client_SelfDirectedWeapon.h"
#include "client_Weapons_defs.h"

class Teleportation: public SelfDirectedWeapon{
	public:
		Teleportation(int ammo = INFINITE);
		~Teleportation();
};

#endif
