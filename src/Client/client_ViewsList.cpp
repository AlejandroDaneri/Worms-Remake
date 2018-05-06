#include "ViewsList.h"

ViewsList::ViewsList(){}

ViewsList::~ViewsList(){}

void ViewsList::addWorm(WormView&& worm, int id){
	this->worms.insert(std::make_pair(id, std::move(worm)));
}

void ViewsList::addWeapon(WeaponView&& weapon, int id){
	this->weapons.insert(std::make_pair(id, std::move(weapon)));
}

void ViewsList::removeWorm(int id){
	auto it = this->worms.find(id);
	it->second.kill();
	this->worms.erase(it);
}

void ViewsList::removeWeapon(int id){
	auto it = this->weapons.find(id);
	it->second.explode();
	this->weapons.erase(it);
}