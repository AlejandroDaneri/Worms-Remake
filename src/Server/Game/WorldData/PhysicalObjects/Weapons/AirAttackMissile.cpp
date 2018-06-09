#include "AirAttackMissile.h"

AirAttackMissile::AirAttackMissile(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(AIR_ATTACK_MISSILE_NAME), parameters.getWeaponRadius(AIR_ATTACK_MISSILE_NAME)){}
		
AirAttackMissile::~AirAttackMissile(){}

const std::string& AirAttackMissile::getName(){
	return AIR_ATTACK_MISSILE_NAME;
}

bool AirAttackMissile::isWindAffected(){
	return true;
}
