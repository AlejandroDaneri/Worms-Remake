#include "client_DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(std::string name, int ammo, bool time, bool fragmentable) :
	Weapon(name, ammo) {
	this->has_Scope = true;
	this->is_Timed = time;
	this->is_Fragmentable = fragmentable;	
}

DistanceWeapon::~DistanceWeapon() {}

DistanceWeapon::DistanceWeapon(DistanceWeapon&& other) : Weapon(std::move(other)){}

bool DistanceWeapon::hasVariablePower(){
	return true;
}

