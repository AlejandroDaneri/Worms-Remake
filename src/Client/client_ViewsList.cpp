#include "ViewsList.h"

ViewsList::ViewsList(WorldView& world): world(world){}

ViewsList::~ViewsList(){}

void ViewsList::removeWorm(int id){
	auto it = this->worms.find(id);
	it->second.kill();
	this->worms.erase(it);
}

void ViewsList::removeWeapon(int id){
	auto it = this->weapons.find(id);
	try{
		it->second.explode();
		this->weapons.erase(it);
	} catch (const std::exception& e){}
}

void ViewsList::updateWormData(int id, int pos_x, int pos_y, int life, char dir){
	auto it = this->worms.find(id);
	Position pos(pos_x, pos_y);
	if (it == this->worms.end()){
		//Worm no existe
		WormView worm(this->world, life, dir, pos);
		this->worms.insert(std::make_pair(id, std::move(worm)));
	} else {
		//Worm existe
		it->second.updateData(life, dir, pos);
	}
}

void ViewsList::updateWeaponData(int id, const std::string& weapon_name, int pos_x, int pos_y){
	auto it = this->weapons.find(id);
	Position pos(pos_x, pos_y);
	if (it == this->weapons.end()){
		//Weapon no existe
		BulletView weapon(this->world, weapon_name, pos);
		this->weapons.insert(std::make_pair(id, std::move(weapon)));
	} else {
		//Weapon existe
		it->second.updateData(pos);
	}
}

void ViewsList::addGirder(size_t size, int pos_x, int pos_y, int rotation){
	GirderView girder(this->world, size, Position(pos_x, pos_y), rotation);
	this->girders.push_back(std::move(girder));
}
