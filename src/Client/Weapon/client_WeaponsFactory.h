#ifndef __CLIENTWEAPONSFACTORY_H__
#define __CLIENTWEAPONSFACTORY_H__

#include "client_Weapon.h"

class WeaponsFactory {
	public:
		WeaponsFactory();
		~WeaponsFactory();
		
		Weapon&& create_weapon(std::string, int ammo);
};


#endif
