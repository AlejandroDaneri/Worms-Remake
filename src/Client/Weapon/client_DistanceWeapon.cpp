#include "client_DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(std::string name, int ammo, bool time) :
	Weapon(name, ammo) {
	this->has_Scope = true;
	this->is_Timed = time;	
}

DistanceWeapon::~DistanceWeapon() {}

DistanceWeapon::DistanceWeapon(DistanceWeapon&& other) : Weapon(std::move(other)){}

bool DistanceWeapon::hasVariablePower() const{
	return true;
}

