#include "server_WeaponFactory.h"
#include "server_Bazooka.h"
#include "server_RedGrenade.h"
#include "server_RedGrenadeFragment.h"

WeaponFactory::WeaponFactory(World& world, GameParameters& parameters):
	world(world), parameters(parameters){}

WeaponFactory::~WeaponFactory(){}

physical_object_ptr WeaponFactory::getWeapon(const std::string& name){
	if (name == "Bazooka"){
		return physical_object_ptr(new Bazooka(this->world, this->parameters));
	} else if (name == "RedGrenade"){
		return physical_object_ptr(new RedGrenade(this->world, this->parameters));
	} else if (name == "RedGrenadeFragment"){
		return physical_object_ptr(new RedGrenadeFragment(this->world, this->parameters));
	}

	return physical_object_ptr();
}