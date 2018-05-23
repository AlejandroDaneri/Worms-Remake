#ifndef __CLIENTWEAPONSFACTORY_H__
#define __CLIENTWEAPONSFACTORY_H__

#include "Weapon.h"
#include <memory>

typedef std::unique_ptr<Weapon> weapon_ptr;

class WeaponsFactory {
	public:
		WeaponsFactory();
		~WeaponsFactory();
		
		weapon_ptr create_weapon(std::string, int ammo);
};


#endif
