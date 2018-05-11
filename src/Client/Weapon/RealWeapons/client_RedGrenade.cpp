#include "client_RedGrenade.h"
#include "client_Weapons_defs.h"

RedGrenade::RedGrenade(int ammo): FragmentableWeapon(RED_GRENADE_NAME, ammo, 
	RED_GRENADE_FRAGMENTS, DEFAULT_TIME) {}

RedGrenade::~RedGrenade() {}

/*weapon_ptr RedGrenade::getFragment(){
	return weapon_ptr(new RedGrenade::Fragment());
}*/

RedGrenade::Fragment::Fragment(): DistanceWeapon(GRENADE_FRAGMENTS_NAME,
	GRENADE_FRAGMENTS_AMMO){}

RedGrenade::Fragment::~Fragment() {}

