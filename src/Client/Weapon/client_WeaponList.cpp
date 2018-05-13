#include "client_WeaponList.h"

WeaponList::WeaponList() {}

WeaponList::~WeaponList() {}

void WeaponList::add(std::string weapon, int ammo) {
	WeaponsFactory factory;
	this->weapons.insert(std::pair<std::string, weapon_ptr>(weapon, std::move(factory.create_weapon(weapon, ammo))));
}

Weapon& WeaponList::get(std::string weapon) {
	return *this->weapons.at(weapon);
}

WeaponList::iterator WeaponList::begin() {
	return this->weapons.begin();
}

WeaponList::iterator WeaponList::end() {
	return this->weapons.end();
}

