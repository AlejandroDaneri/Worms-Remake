#ifndef __WEAPONLIST_H__
#define __WEAPONLIST_H__

#include <map>
#include <string>
#include "PhysicalObject.h"

class GameParameters;

class WeaponList{
	private:
		std::map<std::string, unsigned int> ammo;
		std::string current_weapon;

	public:
		WeaponList();

		~WeaponList();

		void updateAmmo(const std::map<std::string, unsigned int>& ammo);

		bool shoot();

		physical_object_ptr getCurrentWeapon(World& world, GameParameters& parameters);

		void changeWeapon(const std::string& weapon);
};

#endif
