#include "client_DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(std::string name, int ammo, int damage, int radius) :
	Weapon(name, ammo, damage, radius) {
		this->has_Scope = true;	
}

bool DistanceWeapon::hasVariablePower(){
	return true;
}
