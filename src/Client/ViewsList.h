#ifndef __VIEWSLIST_H__
#define __VIEWSLIST_H__

#include <unordered_map>
#include <string>
#include "WorldView.h"
#include "WormView.h"
#include "client_BulletView.h"
#include "GirderView.h"

class ViewsList{
	private:
		WorldView& world;
		std::unordered_map<int, WormView> worms;
		std::unordered_map<int, BulletView> weapons;
		std::unordered_map<int, GirderView> girders;

	public:
		ViewsList(WorldView& world);
		~ViewsList();

		void removeWorm(int id);
		void removeWeapon(int id);
		void removeGirder(int id); ///////////// Probablemente no sirva

		void updateWormData(int id, int pos_x, int pos_y, int life, char dir);

		void updateWeaponData(int id, const std::string& weapon_name, int pos_x, int pos_y);
		
		void updateGirderData(int id, const std::string& girder_name, int pos_x, int pos_y);

		WormView& getWorm(int id){
			return this->worms.at(id);///////////////////////////////////////////////Metodo solo para probar, cuando haya sockets agregar updateWormData y updateWeaponData
		}


};


#endif
