#ifndef __MELEEWEAPON_H__
#define __MELEEWEAPON_H__

#include "Weapon.h"

class MeleeWeapon: public Weapon{
	protected:
		Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power);

	public:
		MeleeWeapon(bool scope, bool timed, int radius, int damage);
		~MeleeWeapon();


};

#endif
