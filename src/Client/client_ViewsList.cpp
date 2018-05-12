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

void ViewsList::removeGirder(int id) {
	auto it = this->girders.find(id);
	it->second.explode();
	this->girders.erase(it);
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
		WeaponView weapon(this->world, weapon_name, pos);
		this->weapons.insert(std::make_pair(id, std::move(weapon)));
	} else {
		//Weapon existe
		it->second.updateData(pos);
	}
}

void updateGirderData(int id, const std::string& girder_name, int pos_x, int pos_y) {
	auto it = this->girders.find(id);
	Position pos(pos_x, pos_y);
	if (it == this->girders.end()){
		//Girder no existe
		GirderView girder(this->world, girder_name, pos);
		this->girders.insert(std::make_pair(id, std::move(girder)));
	} else { ////////////////// Creo que no sirve este caso. Lo dejo por las dudas
		//Girder existe
		it->second.updateData(pos);
	}
}
