#include "PlayerLifeLabel.h"
#include <string>
#include "GamePlayers.h"

const std::string begining("<span color='");
const std::string middle("' font_family=\"monospace\"><b> ");
const std::string ending("</b></span>");

PlayerLifeLabel::PlayerLifeLabel() : id(0), player_name(""), life(0) {
	this->info_label.set_use_markup(true);
	this->id_label.set_use_markup(true);
	this->container.pack_start(this->id_label, Gtk::PACK_SHRINK);
	this->container.pack_start(this->info_label, Gtk::PACK_SHRINK);
}

PlayerLifeLabel::~PlayerLifeLabel() {}

void PlayerLifeLabel::setPlayerName(int id, const std::string& player_name) {
	this->id = id;
	this->player_name = player_name;
	this->updateLabel();
}

void PlayerLifeLabel::addLife(int life) {
	this->life += life;
	this->updateLabel();
}

void PlayerLifeLabel::reduceLife(int life) {
	this->life -= life;
	this->updateLabel();
}

Gtk::HBox& PlayerLifeLabel::getContainer() {
	return this->container;
}

void PlayerLifeLabel::updateLabel() {
	std::string id_message = begining + "white" + middle;
	id_message += std::to_string(this->id) + " " + ending;
	this->id_label.set_markup(id_message);
	this->id_label.override_background_color(Gdk::RGBA(colors[this->id]));
	std::string message = begining + "black" + middle + this->player_name;
	message += ": " + std::to_string(this->life) + ending;
	this->info_label.set_markup(message);
}
