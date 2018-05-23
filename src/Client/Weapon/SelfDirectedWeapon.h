#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "Weapon.h"

class SelfDirectedWeapon: public Weapon{
	public:
		SelfDirectedWeapon(std::string name, int ammo);
		~SelfDirectedWeapon();
		SelfDirectedWeapon(SelfDirectedWeapon&& other);

		bool isSelfDirected() const override;
};

#endif
