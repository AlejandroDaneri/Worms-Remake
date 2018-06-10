#include "WeaponList.h"
#include "WeaponNames.h"
#include "WeaponFactory.h"
#include <map>
#include <string>

WeaponList::WeaponList(): current_weapon(DEFAULT_WEAPON){}

WeaponList::~WeaponList(){}

void WeaponList::updateAmmo(const std::map<std::string, unsigned int>& ammo){
	this->ammo = ammo;
}

bool WeaponList::shoot(){
	if (this->ammo[this->current_weapon] == 0){
		return false;
	}
	this->ammo[this->current_weapon]--;
	return true;
}

physical_object_ptr WeaponList::getCurrentWeapon(World& world,
											GameParameters& parameters){
	WeaponFactory factory(world, parameters);
	return factory.getWeapon(this->current_weapon);
}

void WeaponList::changeWeapon(const std::string& weapon){
	this->current_weapon = weapon;
}
