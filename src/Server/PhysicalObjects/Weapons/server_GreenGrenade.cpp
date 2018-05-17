#include "server_GreenGrenade.h"

GreenGrenade::GreenGrenade(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(GREEN_GRENADE_NAME), parameters.getWeaponRadius(GREEN_GRENADE_NAME)){}
		
GreenGrenade::~GreenGrenade(){}

const std::string& GreenGrenade::getName(){
	return GREEN_GRENADE_NAME;
}
