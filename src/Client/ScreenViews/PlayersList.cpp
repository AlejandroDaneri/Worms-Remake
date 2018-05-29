#include "PlayersList.h"
#include <glibmm/main.h>

PlayersList::PlayersList(){}

PlayersList::~PlayersList(){}

void PlayersList::addPlayer(int id, const std::string& name){
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &PlayersList::addPLayerCallBack), id, name);
    Glib::signal_idle().connect(my_slot);
}

bool PlayersList::addPLayerCallBack(int id, std::string name){
	this->players[id] = name;
	this->labels[id].setPlayerName(name);
	this->container.add(this->labels[id].getLabel());
	return false;
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
