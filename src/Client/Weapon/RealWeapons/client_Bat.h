#ifndef __CLIENTBAT_H__
#define __CLIENTBAT_H__

#include "client_MeleeWeapon.h"
#include "client_Weapons_defs.h"

class Bat: public MeleeWeapon{
	public:
		Bat(int ammo = INFINITE);
		~Bat();
};

#endif
