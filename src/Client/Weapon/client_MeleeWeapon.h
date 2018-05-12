#ifndef __CLIENTMELEEWEAPON_H__
#define __CLIENTMELEEWEAPON_H__

#include "client_Weapon.h"

class MeleeWeapon : public Weapon {
	public:
		MeleeWeapon(std::string name, int ammo, bool scope, bool time = false);
		~MeleeWeapon() {}
};

#endif
