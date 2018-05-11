#ifndef __CLIENTDYNAMITE_H__
#define __CLIENTDYNAMITE_H__

#include "client_MeleeWeapon.h"
#include "client_Weapons_defs.h"

class Dynamite: public MeleeWeapon{
	public:
		Dynamite(int ammo = DYNAMITE_AMMO);
		~Dynamite();
};

#endif
