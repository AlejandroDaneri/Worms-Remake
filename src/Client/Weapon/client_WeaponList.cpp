#include "client_WeaponList.h"

WeaponList::WeaponList() {}

WeaponList::~WeaponList() {}
		
void WeaponList::add(Weapon&& weapon) {
	this->weapons.insert(std::pair<std::string, Weapon>(weapon.getName(), std::move(weapon)));
}

Weapon& WeaponList::get(std::string weapon) {
	return this->weapons.at(weapon);
}

WeaponList::iterator WeaponList::begin() {
	return this->weapons.begin();
}

WeaponList::iterator WeaponList::end() {
	return this->weapons.end();
}

