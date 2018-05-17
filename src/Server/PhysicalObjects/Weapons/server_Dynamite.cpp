#include "server_Dynamite.h"

Dynamite::Dynamite(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(DYNAMITE_NAME), parameters.getWeaponRadius(DYNAMITE_NAME)){}
		
Dynamite::~Dynamite(){}

const std::string& Dynamite::getName(){
	return DYNAMITE_NAME;
}

void Dynamite::setInitialVelocity(){
	this->waiting_to_explode = true;
	this->explode_time.setTime(this->time_to_explode);
	this->explode_time.start();
}
