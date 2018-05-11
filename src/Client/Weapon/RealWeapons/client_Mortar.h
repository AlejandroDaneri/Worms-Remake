#ifndef __CLIENTMORTAR_H__
#define __CLIENTMORTAR_H__

#include "client_FragmentableWeapon.h"


class Mortar: public FragmentableWeapon{
	private:
		class Fragment;

	protected:
		//weapon_ptr getFragment(); AGREGARLO

	public:
		Mortar(int ammo);
		~Mortar();
};

class Mortar::Fragment: public DistanceWeapon {
	public:
		Fragment();
		~Fragment();
};

#endif
