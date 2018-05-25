#include "ViewsList.h"
#include "ObjectSizes.h"
#include "Player.h"

ViewsList::ViewsList(WorldView& world, Player& player, PlayersList& players_list):
	world(world), player(player), players_list(players_list){

	this->scope.set("resources/images/scope/scope.png");
	this->draw_scope = false;
	this->world.addElement(this->scope, Position(0,500), 0, 0);
	this->scope.hide();
	this->current_worm_id = -1;
	this->animation = nullptr;
}

ViewsList::~ViewsList(){}

void ViewsList::removeWorm(int id){
	auto it = this->worms.find(id);
	this->players_list.reducePlayerLife(it->second.getPlayerId(), it->second.getLife());
	if (id == this->current_worm_id){
		this->player.damageReceived();
	}
	it->second.kill();
	this->worms.erase(it);
}

void ViewsList::removeWeapon(int id){
	if (this->weapon_focused == id){
		this->weapon_focused = -1;
	}
	auto it = this->weapons.find(id);
	if (it != this->weapons.end()){
		if (this->animation != nullptr)
			this->animation->join();
		this->animation.reset(new ExplosionView(it->second, *this, id));
		this->animation->start();
	}
}

void ViewsList::eraseWeapon(int id) {
	auto it = this->weapons.find(id);
	if (it != this->weapons.end()) {
		it->second.explode();
		this->weapons.erase(it);
	}
}

void ViewsList::updateWormData(int id, int player_id, float pos_x, float pos_y, int life, char dir, const std::string& weapon_name){
	auto it = this->worms.find(id);
	Position pos(pos_x / UNIT_TO_SEND, pos_y / UNIT_TO_SEND);
	if (it == this->worms.end()){
		//Worm no existe
		WormView worm(this->world, life, dir, pos, player_id, weapon_name);
		this->worms.insert(std::make_pair(id, std::move(worm)));
		this->players_list.addPlayerLife(player_id, life);
	} else {
		//Worm existe
		int current_life = it->second.getLife();
		if (current_life != life){
			this->players_list.reducePlayerLife(player_id, current_life - life);
			if (id == this->current_worm_id){
				this->player.damageReceived();
			}
		}
		it->second.updateData(life, dir, pos, weapon_name);
	}
}

void ViewsList::updateWeaponData(int id, const std::string& weapon_name, float pos_x, float pos_y){
	auto it = this->weapons.find(id);
	Position pos(pos_x / UNIT_TO_SEND, pos_y / UNIT_TO_SEND);
	if (it == this->weapons.end()){
		//Weapon no existe
		BulletView weapon(this->world, weapon_name, pos);
		weapon.setFocus(true);
		if (this->weapon_focused != -1){
			this->weapons.at(weapon_focused).setFocus(false);
		}
		this->weapon_focused = id;
		auto it = this->worms.find(this->current_worm_id);
		if (it != this->worms.end()){
			it->second.setFocus(false);
		}
		this->weapons.insert(std::make_pair(id, std::move(weapon)));
	} else {
		//Weapon existe
		it->second.updateData(pos);
	}
}

void ViewsList::changeWeapon(const std::string &weapon_name) {
    this->worms.at(this->current_worm_id).changeWeapon(weapon_name);
}


void ViewsList::updateScope(int angle) {
	if (this->worms.find(this->current_worm_id) == this->worms.end()){
		return;
	}
	WormView& worm = this->worms.at(this->current_worm_id);
	const char dir = worm.getDir();
	if (dir == -1)
		angle = 180 - angle;
	this->world.moveScope(this->scope, worm.getWidget(), angle);
	this->scope.show();
}

void ViewsList::removeScopeVisibility() {
	this->scope.hide();
}

void ViewsList::addGirder(size_t size, int pos_x, int pos_y, int rotation){
	GirderView girder(this->world, size, Position(pos_x, pos_y), rotation);
	this->girders.push_back(std::move(girder));
}

void ViewsList::setCurrentWorm(int id){
	this->current_worm_id = id;
	this->weapon_focused = -1;
	WormView& worm = this->worms.at(id);
	this->world.setFocus(worm.getWidget());
	worm.setFocus(true);
}