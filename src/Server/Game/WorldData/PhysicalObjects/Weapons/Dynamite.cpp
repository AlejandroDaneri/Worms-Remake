#include "Dynamite.h"

Dynamite::Dynamite(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(DYNAMITE_NAME), parameters.getWeaponRadius(DYNAMITE_NAME)){}
		
Dynamite::~Dynamite(){}

const std::string& Dynamite::getName(){
	return DYNAMITE_NAME;
}
