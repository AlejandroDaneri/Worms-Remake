#include "server_AirAttackMissile.h"

AirAttackMissile::AirAttackMissile(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.get_airAttack_damage(), parameters.get_airAttack_radius()){}
		
AirAttackMissile::~AirAttackMissile(){}

std::string AirAttackMissile::getName(){
	return "AirAttackMissile";
}
