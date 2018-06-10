#ifndef __CLIENTMELEEWEAPON_H__
#define __CLIENTMELEEWEAPON_H__

#include "Weapon.h"
#include <string>

/* Clase que se encarga de representar las armas de cuerpo a cuerpo */
class MeleeWeapon : public Weapon {
public:
	/* Constructor */
	MeleeWeapon(std::string name, int ammo, bool scope, bool time = false);

	/* Destructor */
	~MeleeWeapon() {}

	/* Constructor por movimiento */
	MeleeWeapon(MeleeWeapon&& other);
};

#endif
