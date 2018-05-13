#include "server_Turn.h"

Turn::Turn(): current(0){}

Turn::~Turn(){}

void Turn::addPlayer(Player&& player){
	player.setId(this->players.size());
	this->players.push_back(std::move(player));
}

size_t Turn::get_players_size() const{
	return this->players.size();
}

Player& Turn::getCurrentPlayer(){
	return this->players.at(this->current);
}

void Turn::begin_turn(){
	do {
		this->advanceCurrent();
	} while (! this->getCurrentPlayer().isDead());
	this->getCurrentPlayer().begin_turn();
}

std::vector<Player>& Turn::getPlayers(){
	return this->players;
}

void Turn::advanceCurrent(){
	this->current++;
	if (this->current >= this->players.size()){
		this->current = 0;
	}
}

void Turn::addWorm(World& world, GameParameters& parameters, b2Vec2 position, int id){
	this->players[this->current].addWorm(world, parameters, position, id);
	this->advanceCurrent();
}

void Turn::distributeWorms(size_t size, int life_to_add){
	size = (size / this->players.size()) + 1;
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		it->distributeWorms(size, life_to_add);
	}
}

bool Turn::gameEnded(){
	size_t players_alive = 0;
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		if (!it->isDead()){
			players_alive++;
		}
	}
	return players_alive <= 1;
}
