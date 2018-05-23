#ifndef __CLIENTMELEEWEAPON_H__
#define __CLIENTMELEEWEAPON_H__

#include "Weapon.h"

class MeleeWeapon : public Weapon {
	public:
		MeleeWeapon(std::string name, int ammo, bool scope, bool time = false);
		~MeleeWeapon() {}
		MeleeWeapon(MeleeWeapon&& other);
};

#endif
