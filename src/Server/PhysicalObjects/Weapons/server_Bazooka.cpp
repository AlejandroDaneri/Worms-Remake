#include "server_Bazooka.h"

Bazooka::Bazooka(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(BAZOOKA_NAME), parameters.getWeaponRadius(BAZOOKA_NAME)){}
		
Bazooka::~Bazooka(){}

const std::string& Bazooka::getName(){
	return BAZOOKA_NAME;
}
