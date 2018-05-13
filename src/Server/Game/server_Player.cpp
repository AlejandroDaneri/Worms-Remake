#include "server_Player.h"

Player::Player(Socket&& socket): protocol(std::move(socket)), id(-1){}

Player::Player(Player&& other): 
	protocol(std::move(other.protocol)), worms(std::move(other.worms)), id(other.id){}

Player::~Player(){}

void Player::setId(int id){
	this->id = id;
}

Worm& Player::getCurrentWorm(){
	return this->worms.getCurrentWorm();
}

void Player::begin_turn(){
	this->worms.begin_turn();
}

void Player::addWorm(World& world, GameParameters& parameters, const b2Vec2& position, int id){
	physical_object_ptr worm(new Worm(world, parameters, id, this->id));
	this->worms.add(worm);
	world.addObject(worm, position);
}

void Player::distributeWorms(size_t max, int life_to_add){
	this->worms.distribute(max, life_to_add);
}

ServerProtocol& Player::getProtocol(){
	return this->protocol;
}
