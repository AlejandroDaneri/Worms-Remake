#ifndef __VIEWSLIST_H__
#define __VIEWSLIST_H__

#include <unordered_map>
#include <vector>
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
		std::vector<GirderView> girders;

	public:
		ViewsList(WorldView& world);
		~ViewsList();

		void removeWorm(int id);
		void removeWeapon(int id);

		void updateWormData(int id, float pos_x, float pos_y, int life, char dir);

		void updateWeaponData(int id, const std::string& weapon_name, float pos_x, float pos_y);
		
		void addGirder(size_t size, int pos_x, int pos_y, int rotation);

};


#endif
