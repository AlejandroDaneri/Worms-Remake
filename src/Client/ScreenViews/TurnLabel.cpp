#include "TurnLabel.h"
#include <glibmm/main.h>
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
	std::string message = begining + "Tu turno" + ending;
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &TurnLabel::setLabelCallback), message);
    Glib::signal_idle().connect(my_slot);
}

void TurnLabel::beginTurn(const std::string& player_name) {
	std::string message = begining + "Turno de " + player_name + ending;
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &TurnLabel::setLabelCallback), message);
    Glib::signal_idle().connect(my_slot);
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

bool TurnLabel::setLabelCallback(std::string text){
	this->message.set_markup(text);
	return false;
}
