#ifndef __CLIENTTELEPORTATION_H__
#define __CLIENTTELEPORTATION_H__

#include "SelfDirectedWeapon.h"

class Teleportation: public SelfDirectedWeapon {
	public:
		Teleportation(int ammo);
		~Teleportation();
		Teleportation(Teleportation&& other);
};

#endif
