#include "HolyGrenade.h"
#include <string>

HolyGrenade::HolyGrenade(World& world, GameParameters& parameters):
	Weapon(world, parameters,
		parameters.getWeaponDamage(HOLY_GRENADE_NAME),
		parameters.getWeaponRadius(HOLY_GRENADE_NAME)){}
		
HolyGrenade::~HolyGrenade(){}

const std::string& HolyGrenade::getName(){
	return HOLY_GRENADE_NAME;
}
