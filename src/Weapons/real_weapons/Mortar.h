#ifndef __MORTAR_H__
#define __MORTAR_H__

#include "FragmentableWeapon.h"

class Mortar: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		weapon_ptr getFragment();

	public:
		static const int munitions = 10;
		static const int radius = 2;
		static const int damage = 50;
		static const int fragments = 6;

		Mortar();
		~Mortar();

		bool isTimed();

};

class Mortar::Fragment: public DistanceWeapon{
	public:

		static const int radius = 2;
		static const int damage = 10;

		Fragment();
		~Fragment();

		bool isTimed();
};

#endif