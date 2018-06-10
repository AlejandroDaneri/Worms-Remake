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

		//Actualiza la municion de las armas
		void updateAmmo(const std::map<std::string, unsigned int>& ammo);

		//Devuelve si puede disparar el arma, y disminuye la municion
		bool shoot();

		//Devuelve el arma actual
		physical_object_ptr getCurrentWeapon(World& world, GameParameters& params);

		//Cambia el arma actual
		void changeWeapon(const std::string& weapon);
};

#endif
