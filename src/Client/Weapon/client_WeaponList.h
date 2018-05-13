#ifndef __CLIENTWEAPONLIST_H__
#define __CLIENTWEAPONLIST_H__

#include <map>
#include "client_Weapon.h"

class WeaponList {
	private:
	    typedef std::map<std::string, Weapon> WeaponsList;
		WeaponsList weapons;

	public:
		WeaponList();
		~WeaponList();
		
		void add(Weapon&& weapon);
		
		Weapon& get(std::string weapon);
		
		typedef WeaponsList::iterator iterator;
		typedef WeaponsList::const_iterator const_iterator;
		iterator begin();
		iterator end();
};


#endif
