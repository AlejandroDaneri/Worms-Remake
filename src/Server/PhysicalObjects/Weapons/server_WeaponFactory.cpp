#include "server_WeaponFactory.h"
#include "WeaponNames.h"

#include "server_Bazooka.h"
#include "server_RedGrenade.h"
#include "server_RedGrenadeFragment.h"
#include "server_Banana.h"
#include "server_Teleportation.h"
#include "server_AirAttack.h"
#include "server_AirAttackMissile.h"

WeaponFactory::WeaponFactory(World& world, GameParameters& parameters):
	world(world), parameters(parameters){}

WeaponFactory::~WeaponFactory(){}

physical_object_ptr WeaponFactory::getWeapon(const std::string& name){
	if (name == BAZOOKA_NAME){
		return physical_object_ptr(new Bazooka(this->world, this->parameters));
	} else if (name == RED_GRENADE_NAME){
		return physical_object_ptr(new RedGrenade(this->world, this->parameters));
	} else if (name == RED_GRENADE_FRAGMENTS_NAME){
		return physical_object_ptr(new RedGrenadeFragment(this->world, this->parameters));
	} else if (name == BANANA_NAME){
		return physical_object_ptr(new Banana(this->world, this->parameters));
	} else if (name == TELEPORT_NAME){
		return physical_object_ptr(new Teleportation(this->world, this->parameters));
	} else if (name == AIR_ATTACK_NAME){
		return physical_object_ptr(new AirAttack(this->world, this->parameters));
	} else if (name == AIR_ATTACK_MISSILE_NAME){
		return physical_object_ptr(new AirAttackMissile(this->world, this->parameters));
	}

	throw std::runtime_error(name + ": El arma no existe.");
}