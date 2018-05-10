#include "server_WeaponFactory.h"

WeaponFactory::WeaponFactory(World& world, GameParameters& parameters):
	world(world), parameters(parameters){}

WeaponFactory::~WeaponFactory(){}

physical_object_ptr WeaponFactory::getWeapon(const std::string& name){
	//if (name == "Bazooka"){
		return physical_object_ptr(new Bazooka(this->world, this->parameters));
	//}
}