#ifndef __CLIENTDYNAMITE_H__
#define __CLIENTDYNAMITE_H__

#include "client_MeleeWeapon.h"

class Dynamite: public MeleeWeapon {
	public:
		Dynamite(int ammo);
		~Dynamite();
		Dynamite(Dynamite&& other);
};

#endif
