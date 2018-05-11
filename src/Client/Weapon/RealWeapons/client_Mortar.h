#ifndef __CLIENTMORTAR_H__
#define __CLIENTMORTAR_H__

#include "client_FragmentableWeapon.h"
#include "client_Weapons_defs.h"

class Mortar: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		//weapon_ptr getFragment(); AGREGARLO

	public:
		Mortar(int ammo = MORTAR_AMMO);
		~Mortar();
};

class Mortar::Fragment: public DistanceWeapon {
	public:
		Fragment();
		~Fragment();
};

#endif
