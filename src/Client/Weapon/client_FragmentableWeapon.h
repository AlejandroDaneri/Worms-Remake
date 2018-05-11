#ifndef __CLIENTFRAGMENTABLEWEAPON_H__
#define __CLIENTFRAGMENTABLEWEAPON_H__

#include "client_DistanceWeapon.h"

class FragmentableWeapon: public DistanceWeapon{
	private:
		int fragments;

	protected:
		//virtual weapon_ptr getFragment() = 0;

	public:
		FragmentableWeapon(std::string name, int munitions, int damage, int radius, int fragments, int time = -1);
		~FragmentableWeapon();

		//virtual void shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time);
};

#endif
