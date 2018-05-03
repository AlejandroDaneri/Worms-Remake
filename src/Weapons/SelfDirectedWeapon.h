#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "Weapon.h"

class SelfDirectedWeapon: public Weapon{
	protected:
		Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power);

	public:
		SelfDirectedWeapon(int radius, int damage);
		~SelfDirectedWeapon();

		void shoot(const Position& pos);

};

#endif