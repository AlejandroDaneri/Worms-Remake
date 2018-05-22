#include "client_PlayersList.h"

PlayersList::PlayersList(){}

PlayersList::~PlayersList(){}

void PlayersList::addPlayer(int id, const std::string& name){
	this->players[id] = name;
	this->labels[id].setPlayerName(name);
	this->container.add(this->labels[id].getLabel());
}

const std::string& PlayersList::getPlayer(int id) const{
	return this->players.at(id);
}

Gtk::Container& PlayersList::getWindow(){
	return this->container;
}

void PlayersList::addPlayerLife(int player_id, int life){
	this->labels[player_id].addLife(life);
}

void PlayersList::reducePlayerLife(int player_id, int life){
	this->labels[player_id].reduceLife(life);
}
