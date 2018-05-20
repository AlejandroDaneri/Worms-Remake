#include "client_PlayersList.h"

#include <iostream>//////////////////////////////

PlayersList::PlayersList(){}

PlayersList::~PlayersList(){}

void PlayersList::addPlayer(int id, const std::string& name){
	this->players[id] = name;
	std::cout <<"player_added: id "<<id<<" name: "<<this->players[id]<<std::endl;
}

const std::string& PlayersList::getPlayer(int id) const{
	return this->players.at(id);
}