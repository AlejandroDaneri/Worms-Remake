#include "Weapon.h"

Weapon::Weapon(std::string name, int ammo) :
	name(name), ammo(ammo), has_Scope(false), is_Timed(false){}
	
Weapon::~Weapon() {}

Weapon::Weapon(Weapon&& other) {
	this->name = std::move(other.name);
	this->ammo = std::move(other.ammo);
	this->has_Scope = std::move(other.has_Scope);
	this->is_Timed = std::move(other.is_Timed);
}

Weapon& Weapon::operator=(Weapon&& other) {
	this->name = std::move(other.name);
	this->ammo = std::move(other.ammo);
	this->has_Scope = std::move(other.has_Scope);
	this->is_Timed = std::move(other.is_Timed);
	return *this;
}

bool Weapon::hasScope() const{
	return this->has_Scope;
}

bool Weapon::isSelfDirected() const{
	return false;
}

bool Weapon::isTimed() const{
	return this->is_Timed;
}

bool Weapon::hasVariablePower() const{
	return false;
}

const std::string& Weapon::getName() const{
	return this->name;
}

void Weapon::shoot() {
	if (this->ammo <= 100)
		this->ammo--;
}

bool Weapon::hasAmmo() const{
	return this->ammo > 0;
}

unsigned int Weapon::getAmmo() const{
	return this->ammo;
}

