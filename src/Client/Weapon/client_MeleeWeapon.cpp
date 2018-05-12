#include "client_MeleeWeapon.h"
#include <limits>

MeleeWeapon::MeleeWeapon(std::string name, int ammo, bool scope, bool time) :
	Weapon(name, ammo) {
	this->has_Scope = scope;
	this->is_Timed = time;
}

