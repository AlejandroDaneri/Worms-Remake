#include "RedGrenadeFragment.h"
#include <string>

RedGrenadeFragment::RedGrenadeFragment(World& world, GameParameters& params):
	Fragment(world, params,
		params.getWeaponDamage(RED_GRENADE_FRAGMENTS_NAME),
		params.getWeaponRadius(RED_GRENADE_FRAGMENTS_NAME)){}
		
RedGrenadeFragment::~RedGrenadeFragment(){}

const std::string& RedGrenadeFragment::getName(){
	return RED_GRENADE_FRAGMENTS_NAME;
}
