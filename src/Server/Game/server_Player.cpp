#include "server_Player.h"

Player::Player(Socket&& socket): protocol(std::move(socket)){}

Player::Player(Player&& other): 
	protocol(std::move(other.protocol)), worms(std::move(other.worms)){}

Player::~Player(){}

worm_ptr Player::getCurrentWorm(){
	return this->worms.getCurrentWorm();
}

void Player::begin_turn(){
	this->worms.begin_turn();
}

void Player::add_worm(World& world, int id, const b2Vec2& position){
	physical_object_ptr worm(new Worm(world, id));
	this->worms.add(worm);
	world.addObject(worm, position);
}