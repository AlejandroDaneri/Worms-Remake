#include "WeaponFactory.h"
#include "WeaponNames.h"

#include "Bazooka.h"
#include "Dynamite.h"
#include "RedGrenade.h"
#include "RedGrenadeFragment.h"
#include "GreenGrenade.h"
#include "HolyGrenade.h"
#include "Banana.h"
#include "Teleportation.h"
#include "AirAttack.h"
#include "AirAttackMissile.h"
#include "Mortar.h"
#include "MortarFragment.h"
#include "Bat.h"

WeaponFactory::WeaponFactory(World& world, GameParameters& parameters):
	world(world), parameters(parameters){}

WeaponFactory::~WeaponFactory(){}

physical_object_ptr WeaponFactory::getWeapon(const std::string& name){
	if (name == BAZOOKA_NAME){
		return physical_object_ptr(new Bazooka(this->world, this->parameters));
	} else if (name == DYNAMITE_NAME){
		return physical_object_ptr(new Dynamite(this->world, this->parameters));
	} else if (name == RED_GRENADE_NAME){
		return physical_object_ptr(new RedGrenade(this->world, this->parameters));
	} else if (name == RED_GRENADE_FRAGMENTS_NAME){
		return physical_object_ptr(new RedGrenadeFragment(this->world, this->parameters));
	} else if (name == GREEN_GRENADE_NAME){
		return physical_object_ptr(new GreenGrenade(this->world, this->parameters));
	} else if (name == HOLY_GRENADE_NAME){
		return physical_object_ptr(new HolyGrenade(this->world, this->parameters));
	} else if (name == MORTAR_NAME){
		return physical_object_ptr(new Mortar(this->world, this->parameters));
	} else if (name == MORTAR_FRAGMENTS_NAME){
		return physical_object_ptr(new MortarFragment(this->world, this->parameters));	
	} else if (name == BANANA_NAME){
		return physical_object_ptr(new Banana(this->world, this->parameters));
	} else if (name == BAT_NAME){
		return physical_object_ptr(new Bat(this->world, this->parameters));
	} else if (name == TELEPORT_NAME){
		return physical_object_ptr(new Teleportation(this->world, this->parameters));
	} else if (name == AIR_ATTACK_NAME){
		return physical_object_ptr(new AirAttack(this->world, this->parameters));
	} else if (name == AIR_ATTACK_MISSILE_NAME){
		return physical_object_ptr(new AirAttackMissile(this->world, this->parameters));
	}

	throw std::runtime_error(name + ": El arma no existe.");
}
