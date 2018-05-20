#include "client_PlayersList.h"

PlayersList::PlayersList(){}

PlayersList::~PlayersList(){}

void PlayersList::addPlayer(int id, const std::string& name){
	this->players[id] = name;
}

const std::string& PlayersList::getPlayer(int id) const{
	return this->players.at(id);
}