#ifndef __CLIENTWEAPONLIST_H__
#define __CLIENTWEAPONLIST_H__

#include <map>
#include "client_Weapon.h"
#include "client_WeaponsFactory.h"

class WeaponList {
	private:
	    typedef std::map<std::string, weapon_ptr> WeaponsList;
		WeaponsList weapons;
		std::string actual_weapon;

	public:
		WeaponList();
		~WeaponList();
		
		void add(std::string weapon, int ammo);
		
		Weapon& get_actual_weapon();
		
		void change_weapon(std::string weapon);
		
		typedef WeaponsList::iterator iterator;
		typedef WeaponsList::const_iterator const_iterator;
		iterator begin();
		iterator end();
};


#endif
