#include "MeleeWeapon.h"
#include <limits>
#include <string>

MeleeWeapon::MeleeWeapon(std::string name, int ammo, bool scope, bool time) :
		Weapon(name, ammo) {
	this->has_Scope = scope;
	this->is_Timed = time;
}

MeleeWeapon::MeleeWeapon(MeleeWeapon&& other) : Weapon(std::move(other)) {}

