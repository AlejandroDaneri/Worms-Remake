#include "client_Weapon.h"

Weapon::Weapon(std::string name, int ammo) :
	name(name), ammo(ammo), has_Scope(false), is_Timed(false),
	is_Fragmentable(false) {}
	
Weapon::~Weapon() {}

Weapon::Weapon(Weapon&& other) {
	this->name = std::move(other.name);
	this->ammo = std::move(other.ammo);
	this->has_Scope = std::move(other.has_Scope);
	this->is_Timed = std::move(other.is_Timed);
	this->is_Fragmentable = std::move(other.is_Fragmentable);
}

Weapon& Weapon::operator=(Weapon&& other) {
	this->name = std::move(other.name);
	this->ammo = std::move(other.ammo);
	this->has_Scope = std::move(other.has_Scope);
	this->is_Timed = std::move(other.is_Timed);
	this->is_Fragmentable = std::move(other.is_Fragmentable);
	return *this;
}

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

