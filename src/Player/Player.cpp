#include "Player.h"

Player::Player(std::vector<Worm>&& worms): worms(std::move(worms)){}

Player::~Player(){}

Worm& Player::getCurrentWorm(){
	return this->worms.getCurrentWorm();
}

void Player::begin_turn(){
	weapon_ptr weapon = std::move(this->worms.getCurrentWorm().getWeapon());
	this->worms.changeWorm();
	this->worms.getCurrentWorm().set_weapon(std::move(weapon));
}