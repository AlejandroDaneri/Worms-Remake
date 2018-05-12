#include "client_Weapon.h"

Weapon::Weapon(std::string name, int ammo) :
	name(name), ammo(ammo), has_Scope(false), is_Timed(false),
	is_Fragmentable(false) {}
	
Weapon::~Weapon() {}

bool Weapon::hasScope() {
	return this->has_Scope;
}

bool Weapon::isSelfDirected() {
	return false;
}

bool Weapon::isFragmentable() {
	return this->is_Fragmentable;
}

bool Weapon::isTimed() {
	return this->is_Timed;
}

bool Weapon::hasVariablePower() {
	return false;
}

std::string Weapon::getName() {
	return this->name;
}

void Weapon::shoot() {
	this->ammo--;
}

bool Weapon::hasAmmo() {
	return this->ammo > 0;
}

