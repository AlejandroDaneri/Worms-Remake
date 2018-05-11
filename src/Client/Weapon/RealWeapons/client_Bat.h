#ifndef __CLIENTBAT_H__
#define __CLIENTBAT_H__

#include "client_MeleeWeapon.h"

class Bat: public MeleeWeapon{
	public:
		Bat(int ammo);
		~Bat();
};

#endif
