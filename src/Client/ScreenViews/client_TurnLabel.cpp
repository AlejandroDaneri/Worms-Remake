#include "TurnLabel.h"
#include <string>

const std::string begining("<span size='20000'>");
const std::string ending("</span>");

TurnLabel::TurnLabel(){
	this->label.set_use_markup(true);
	this->label.set_markup(begining + "Worms" + ending);
}

TurnLabel::~TurnLabel(){}

void TurnLabel::beginTurn(){
	this->label.set_markup(begining + "Empieza tu turno" + ending);
}

void TurnLabel::endTurn(){
	this->label.set_markup(begining + "Termino tu turno" + ending);
}
		
Gtk::Label& TurnLabel::getWindow(){
	return this->label;
}