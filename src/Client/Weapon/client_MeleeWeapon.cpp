#include "client_MeleeWeapon.h"
#include <limits>

MeleeWeapon::MeleeWeapon(std::string name, int ammo, bool scope, int time) :
	Weapon(name, ammo) {
	this->has_Scope = scope;
	this->is_Timed = time > 0;
	this->time = time;
}

void MeleeWeapon::changeTime(int time) {
	if (this->is_Timed)
		this->time = time;
}

int MeleeWeapon::getTime() {
	return this->time;
}

