#include "RedGrenade.h"
#include <string>

RedGrenade::RedGrenade(World& world, GameParameters& parameters):
	FragmentableWeapon(world, parameters,
		parameters.getWeaponDamage(RED_GRENADE_NAME),
		parameters.getWeaponFragments(RED_GRENADE_NAME),
		parameters.getWeaponRadius(RED_GRENADE_NAME)){}

RedGrenade::~RedGrenade(){}

const std::string& RedGrenade::getName(){
	return RED_GRENADE_NAME;
}
