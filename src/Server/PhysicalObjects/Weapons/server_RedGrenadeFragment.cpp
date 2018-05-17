#include "server_RedGrenadeFragment.h"

RedGrenadeFragment::RedGrenadeFragment(World& world, GameParameters& parameters):
	Fragment(world, parameters, parameters.getWeaponDamage(RED_GRENADE_FRAGMENTS_NAME), parameters.getWeaponRadius(RED_GRENADE_FRAGMENTS_NAME)){}
		
RedGrenadeFragment::~RedGrenadeFragment(){}

const std::string& RedGrenadeFragment::getName(){
	return RED_GRENADE_FRAGMENTS_NAME;
}
