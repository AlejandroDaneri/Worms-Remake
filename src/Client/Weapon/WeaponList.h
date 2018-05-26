#ifndef __CLIENTWEAPONLIST_H__
#define __CLIENTWEAPONLIST_H__

#include <map>
#include "Weapon.h"
#include "WeaponsFactory.h"

class WeaponList {
	private:
	    typedef std::map<std::string, weapon_ptr> WeaponsList;
		WeaponsList weapons;
		std::string current_weapon;

	public:
		WeaponList();
		~WeaponList();
		
		void add(std::string weapon, int ammo);
		
		Weapon& get_current_weapon();
		
		void change_weapon(std::string weapon);
		
		typedef WeaponsList::iterator iterator;
		typedef WeaponsList::const_iterator const_iterator;
		iterator begin();
		iterator end();
};


#endif
