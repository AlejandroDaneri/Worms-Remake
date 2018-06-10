#include "Mortar.h"
#include <string>

Mortar::Mortar(World& world, GameParameters& parameters):
	FragmentableWeapon(world, parameters,
		parameters.getWeaponDamage(MORTAR_NAME),
		parameters.getWeaponFragments(MORTAR_NAME),
		parameters.getWeaponRadius(MORTAR_NAME)){}

Mortar::~Mortar(){}

const std::string& Mortar::getName(){
    return MORTAR_NAME;
}

bool Mortar::isWindAffected(){
	return true;
}
