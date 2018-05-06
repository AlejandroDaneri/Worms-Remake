#ifndef __VIEWSLIST_H__
#define __VIEWSLIST_H__

#include <unordered_map>
#include "WormView.h"
#include "WeaponView.h"

class ViewsList{
	private:
		std::unordered_map<int, WormView> worms;
		std::unordered_map<int, WeaponView> weapons;

	public:
		ViewsList();
		~ViewsList();

		void addWorm(WormView&& worm, int id);
		void addWeapon(WeaponView&& weapon, int id);

		void removeWorm(int id);
		void removeWeapon(int id);

		WormView& getWorm(int id){
			return this->worms.at(id);///////////////////////////////////////////////Metodo solo para probar, cuando haya sockets agregar updateWormData y updateWeaponData
		}


};


#endif
