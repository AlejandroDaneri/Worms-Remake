#include "client_Mortar.h"
#include "client_Weapons_defs.h"

Mortar::Mortar(int ammo): FragmentableWeapon(MORTAR_NAME, ammo,
	MORTAR_FRAGMENTS) {}

Mortar::~Mortar() {}

/*weapon_ptr Mortar::getFragment(){
	return weapon_ptr(new Mortar::Fragment());
}*/

Mortar::Fragment::Fragment(): DistanceWeapon(FRAGMENTS_NAME, FRAGMENTS_AMMO) {}

Mortar::Fragment::~Fragment(){}

