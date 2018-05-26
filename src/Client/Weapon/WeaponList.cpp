#include "WeaponList.h"
#include "WeaponNames.h"

WeaponList::WeaponList(): current_weapon(DEFAULT_WEAPON){}

WeaponList::~WeaponList() {}

void WeaponList::add(std::string weapon, int ammo) {
	WeaponsFactory factory;
	this->weapons.insert(std::pair<std::string, weapon_ptr>(weapon, std::move(factory.create_weapon(weapon, ammo))));
}

void WeaponList::change_weapon(std::string weapon) {
	this->current_weapon = weapon;
}

Weapon& WeaponList::get_current_weapon() {
	return *this->weapons.at(this->current_weapon);
}

WeaponList::iterator WeaponList::begin() {
	return this->weapons.begin();
}

WeaponList::iterator WeaponList::end() {
	return this->weapons.end();
}

