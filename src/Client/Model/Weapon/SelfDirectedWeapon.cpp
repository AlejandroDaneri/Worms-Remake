#include "SelfDirectedWeapon.h"
#include <string>

SelfDirectedWeapon::SelfDirectedWeapon(std::string name, int ammo) : Weapon(
		name, ammo) {}

SelfDirectedWeapon::~SelfDirectedWeapon() {}

SelfDirectedWeapon::SelfDirectedWeapon(SelfDirectedWeapon&& other) : Weapon(
		std::move(other)) {}

bool SelfDirectedWeapon::isSelfDirected() const {
	return true;
}

