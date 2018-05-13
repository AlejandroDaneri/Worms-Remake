#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "client_Weapon.h"

class SelfDirectedWeapon: public Weapon{
	public:
		SelfDirectedWeapon(std::string name, int ammo);
		~SelfDirectedWeapon();
		SelfDirectedWeapon(SelfDirectedWeapon&& other);

		bool isSelfDirected() override;
};

#endif
