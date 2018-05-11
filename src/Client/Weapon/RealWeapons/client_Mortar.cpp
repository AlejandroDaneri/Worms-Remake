#include "client_Mortar.h"

Mortar::Mortar(int ammo): FragmentableWeapon(MORTAR_NAME, ammo,	MORTAR_RADIUS,
	MORTAR_DAMAGE, MORTAR_FRAGMENTS) {}

Mortar::~Mortar() {}

/*weapon_ptr Mortar::getFragment(){
	return weapon_ptr(new Mortar::Fragment());
}*/

Mortar::Fragment::Fragment(): DistanceWeapon(FRAGMENTS_NAME, FRAGMENTS_AMMO,
	FRAGMENTS_DAMAGE, FRAGMENTS_RADIUS) {}

Mortar::Fragment::~Fragment(){}

