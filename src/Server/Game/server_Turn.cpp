#include "server_Turn.h"

Turn::Turn(): current(-1){}

Turn::~Turn(){}

void Turn::addPlayer(Player&& player){
	this->players.push_back(std::move(player));
	this->current++;
}

size_t Turn::get_players_size() const{
	return this->players.size();
}

Player& Turn::getCurrentPlayer(){
	return this->players.at(this->current);
}

void Turn::begin_turn(){
	++ this->current;
	if (this->current >= this->players.size()){
		this->current = 0;
	}
	this->getCurrentPlayer().begin_turn();
}

std::vector<Player>& Turn::getPlayers(){
	return this->players;
}
