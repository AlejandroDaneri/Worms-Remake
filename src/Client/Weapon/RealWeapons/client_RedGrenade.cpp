#include "client_RedGrenade.h"

RedGrenade::RedGrenade(int ammo): FragmentableWeapon(RED_GRENADE_NAME, ammo, 
	RED_GRENADE_DAMAGE, RED_GRENADE_RADIUS, RED_GRENADE_FRAGMENTS, DEFAULT_TIME) {}

RedGrenade::~RedGrenade() {}

/*weapon_ptr RedGrenade::getFragment(){
	return weapon_ptr(new RedGrenade::Fragment());
}*/

RedGrenade::Fragment::Fragment(): DistanceWeapon(GRENADE_FRAGMENTS_NAME,
	GRENADE_FRAGMENTS_AMMO, GRENADE_FRAGMENTS_DAMAGE, GRENADE_FRAGMENTS_RADIUS){}

RedGrenade::Fragment::~Fragment() {}

