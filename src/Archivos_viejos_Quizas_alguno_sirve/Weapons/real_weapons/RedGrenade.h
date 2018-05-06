#ifndef __REDGRENADE_H__
#define __REDGRENADE_H__

#include "FragmentableWeapon.h"

class RedGrenade: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		weapon_ptr getFragment();

	public:
		static const int munitions = 10;
		static const int radius = 2;
		static const int damage = 30;
		static const int fragments = 6;

		RedGrenade();
		~RedGrenade();

		bool isTimed();

};

class RedGrenade::Fragment: public DistanceWeapon{
	public:

		static const int radius = 2;
		static const int damage = 10;

		Fragment();
		~Fragment();

		bool isTimed();
};

#endif