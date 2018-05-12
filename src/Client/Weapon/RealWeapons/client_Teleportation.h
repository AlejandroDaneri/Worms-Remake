#ifndef __CLIENTTELEPORTATION_H__
#define __CLIENTTELEPORTATION_H__

#include "client_SelfDirectedWeapon.h"

class Teleportation: public SelfDirectedWeapon {
	public:
		Teleportation(int ammo);
		~Teleportation();
};

#endif
