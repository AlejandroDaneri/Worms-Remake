#include "client_WeaponList.h"

WeaponList::WeaponList() {
	this->actual_weapon = "";///////////////////////////////////////////////
}

WeaponList::~WeaponList() {}

void WeaponList::add(std::string weapon, int ammo) {
	if (this->actual_weapon == "")
		this->actual_weapon = weapon;
	WeaponsFactory factory;
	this->weapons.insert(std::pair<std::string, weapon_ptr>(weapon, std::move(factory.create_weapon(weapon, ammo))));
}

void WeaponList::change_weapon(std::string weapon) {
	this->actual_weapon = weapon;
}

Weapon& WeaponList::get_actual_weapon() {
	return *this->weapons.at(this->actual_weapon);
}

WeaponList::iterator WeaponList::begin() {
	return this->weapons.begin();
}

WeaponList::iterator WeaponList::end() {
	return this->weapons.end();
}

