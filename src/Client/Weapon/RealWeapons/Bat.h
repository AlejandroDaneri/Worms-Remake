#ifndef __CLIENTBAT_H__
#define __CLIENTBAT_H__

#include "MeleeWeapon.h"

class Bat: public MeleeWeapon {
	public:
		Bat(int ammo);
		~Bat();
		Bat(Bat&& other);
};

#endif