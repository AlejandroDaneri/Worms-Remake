#ifndef __CLIENTWEAPONLIST_H__
#define __CLIENTWEAPONLIST_H__

#include <map>
#include "Weapon.h"
#include "WeaponsFactory.h"

/* Clase que se encarga de almacenar las armas del juego */
class WeaponList {
	private:
	    typedef std::map<std::string, weapon_ptr> WeaponsList;
		WeaponsList weapons;
		std::string current_weapon;

	public:
		/* Constructor */
		WeaponList();

		/* Destructor */
		~WeaponList();


		/* Agrega un arma a la lista */
		void add(std::string weapon, int ammo);

		/* Devuelve el arma actual */
		Weapon& get_current_weapon();
		
		/* Cambia el arma actual por la especificada */
		void change_weapon(std::string weapon);

		typedef WeaponsList::iterator iterator;
		typedef WeaponsList::const_iterator const_iterator;
		iterator begin();
		iterator end();
};


#endif
