#include "WeaponList.h"
#include "WeaponNames.h"

WeaponList::WeaponList(): current_weapon(DEFAULT_WEAPON){}

WeaponList::~WeaponList() {}

void WeaponList::add(std::string weapon, int ammo) {
	WeaponsFactory factory;
	this->weapons.insert(std::pair<std::string, weapon_ptr>(weapon, std::move(factory.createWeapon(weapon, ammo))));
}

void WeaponList::changeWeapon(std::string weapon) {
	this->current_weapon = weapon;
}

Weapon& WeaponList::getCurrentWeapon() {
	return *this->weapons.at(this->current_weapon);
}

WeaponList::iterator WeaponList::begin() {
	return this->weapons.begin();
}

WeaponList::iterator WeaponList::end() {
	return this->weapons.end();
}

