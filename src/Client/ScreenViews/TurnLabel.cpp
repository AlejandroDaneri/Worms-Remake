#include "TurnLabel.h"
#include <string>

const std::string begining("<span size='20000'>");
const std::string ending("</span>");

TurnLabel::TurnLabel() {
	this->message.set_use_markup(true);
	this->message.set_markup(begining + "Worms" + ending);
	this->label.pack_start(this->message);
	this->label.pack_end(this->time);
}

TurnLabel::~TurnLabel() {}

void TurnLabel::beginTurn() {
	this->message.set_markup(begining + "Tu turno" + ending);
}

void TurnLabel::beginTurn(const std::string& player_name) {
	this->message.set_markup(begining + "Turno de " + player_name + ending);
}

void TurnLabel::endTurn() {
	this->time.set_markup("");
	this->message.set_markup(begining + "Termino tu turno" + ending);
}

void TurnLabel::setTime(int time) {
	this->time.set_markup(begining + std::to_string(time) + ending);
}
		
Gtk::Container& TurnLabel::getWindow() {
	return this->label;
}