#include "client_DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(std::string name, int ammo, int damage,
	int radius, int time) : Weapon(name, ammo, damage, radius) {
	this->has_Scope = true;
	this->is_Timed = time > 0;
	this->time = time;	
}

bool DistanceWeapon::hasVariablePower(){
	return true;
}

void DistanceWeapon::changeTime(int time) {
	if (this->is_Timed)
		this->time = time;
}

int DistanceWeapon::getTime() {
	return this->time;
}
