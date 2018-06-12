#include "PlayersList.h"
#include <glibmm/main.h>
#include <string>

#define SPACING 20

PlayersList::PlayersList() : container(false, SPACING) {
	this->title.set_use_markup(true);
	this->title.set_markup("<span><b><u>Jugadores</u></b></span>");
	this->container.pack_start(this->title, Gtk::PACK_SHRINK);
}

PlayersList::~PlayersList() {}

void PlayersList::addPlayer(int id, const std::string& name) {
	sigc::slot<bool> my_slot = sigc::bind(
			sigc::mem_fun(*this, &PlayersList::addPlayerCallBack), id, name);
	Glib::signal_idle().connect(my_slot);
}

bool PlayersList::addPlayerCallBack(int id, std::string name) {
	this->players[id] = name;
	this->labels[id].setPlayerName(id, name);
	this->container.pack_start(this->labels[id].getLabel(), Gtk::PACK_SHRINK);
	return false;
}

const std::string& PlayersList::getPlayer(int id) const {
	return this->players.at(id);
}

Gtk::Container& PlayersList::getWindow() {
	return this->container;
}

void PlayersList::addPlayerLife(int player_id, int life) {
	this->labels[player_id].addLife(life);
}

void PlayersList::reducePlayerLife(int player_id, int life) {
	this->labels[player_id].reduceLife(life);
}
