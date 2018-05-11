#ifndef __CLIENTREDGRENADE_H__
#define __CLIENTREDGRENADE_H__

#include "client_FragmentableWeapon.h"
#include "client_Weapons_defs.h"

class RedGrenade: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		//weapon_ptr getFragment(); AGREGARLO

	public:
		RedGrenade(int ammo = RED_GRENADE_AMMO);
		~RedGrenade();
};

class RedGrenade::Fragment: public DistanceWeapon{
	public:
		Fragment();
		~Fragment();
};

#endif
