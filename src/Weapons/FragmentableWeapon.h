#ifndef __FRAGMENTABLEWEAPON_H__
#define __FRAGMENTABLEWEAPON_H__

#include "DistanceWeapon.h"

class FragmentableWeapon: public DistanceWeapon{
	private:
		int fragments;

	protected:
		virtual weapon_ptr getFragment() = 0;

	public:
		FragmentableWeapon(int fragments, bool timed, int radius, int damage);
		~FragmentableWeapon();

		virtual void shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time);

};

#endif