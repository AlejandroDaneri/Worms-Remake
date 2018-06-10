#include "WeaponFactory.h"
#include "WeaponNames.h"
#include <string>

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
		return physical_object_ptr(new Bazooka(world, parameters));
	} else if (name == DYNAMITE_NAME){
		return physical_object_ptr(new Dynamite(world, parameters));
	} else if (name == RED_GRENADE_NAME){
		return physical_object_ptr(new RedGrenade(world, parameters));
	} else if (name == RED_GRENADE_FRAGMENTS_NAME){
		return physical_object_ptr(new RedGrenadeFragment(world, parameters));
	} else if (name == GREEN_GRENADE_NAME){
		return physical_object_ptr(new GreenGrenade(world, parameters));
	} else if (name == HOLY_GRENADE_NAME){
		return physical_object_ptr(new HolyGrenade(world, parameters));
	} else if (name == MORTAR_NAME){
		return physical_object_ptr(new Mortar(world, parameters));
	} else if (name == MORTAR_FRAGMENTS_NAME){
		return physical_object_ptr(new MortarFragment(world, parameters));	
	} else if (name == BANANA_NAME){
		return physical_object_ptr(new Banana(world, parameters));
	} else if (name == BAT_NAME){
		return physical_object_ptr(new Bat(world, parameters));
	} else if (name == TELEPORT_NAME){
		return physical_object_ptr(new Teleportation(world, parameters));
	} else if (name == AIR_ATTACK_NAME){
		return physical_object_ptr(new AirAttack(world, parameters));
	} else if (name == AIR_ATTACK_MISSILE_NAME){
		return physical_object_ptr(new AirAttackMissile(world, parameters));
	}

	throw std::runtime_error(name + ": El arma no existe.");
}
