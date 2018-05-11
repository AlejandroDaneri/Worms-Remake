#ifndef __CLIENTBANANA_H__
#define __CLIENTBANANA_H__

#include "client_DistanceWeapon.h"

class Banana: public DistanceWeapon {
	public:
		Banana(int ammo);
		~Banana();

		//virtual void shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time);
};

#endif
