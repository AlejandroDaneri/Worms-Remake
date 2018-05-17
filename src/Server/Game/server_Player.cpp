#include "server_Player.h"

Player::Player(Socket&& socket, const std::string& name): protocol(std::move(socket)), name(name), id(-1){}

Player::Player(Player&& other): 
	protocol(std::move(other.protocol)), name(std::move(other.name)), worms(std::move(other.worms)), id(other.id){}

Player::~Player(){}

void Player::setId(int id){
	this->id = id;
}

int Player::getId() const{
	return this->id;
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

bool Player::isDead(){
	return this->worms.isEmpty();
}

ServerProtocol& Player::getProtocol(){
	return this->protocol;
}

const std::string& Player::getName() const{
	return this->name;
}
