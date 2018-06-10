#ifndef __CLIENTWEAPONSFACTORY_H__
#define __CLIENTWEAPONSFACTORY_H__

#include <memory>
#include <string>
#include "Weapon.h"

typedef std::unique_ptr<Weapon> weapon_ptr;

/* Clase que se encarga de crear las armas del juego */
class WeaponsFactory {
public:
	/* Constructor */
	WeaponsFactory();

	/* Destructor */
	~WeaponsFactory();


	/* Crea el arma especificada con las municiones especificadas */
	weapon_ptr createWeapon(std::string weapon, int ammo);
};


#endif
