#include "server_Bazooka.h"

Bazooka::Bazooka(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.get_bazooka_damage(), parameters.get_bazooka_radius()){}
		
Bazooka::~Bazooka(){}

std::string Bazooka::getName(){
	return "Bazooka";
}
