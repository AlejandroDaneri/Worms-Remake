#ifndef __CLIENTREDGRENADE_H__
#define __CLIENTREDGRENADE_H__

#include "client_FragmentableWeapon.h"

class RedGrenade: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		//weapon_ptr getFragment(); AGREGARLO

	public:
		RedGrenade(int ammo);
		~RedGrenade();
};

class RedGrenade::Fragment: public DistanceWeapon{
	public:
		Fragment();
		~Fragment();
};

#endif
