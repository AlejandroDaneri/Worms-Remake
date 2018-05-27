#include "GameMenuField.h"

GameMenuField::GameMenuField(const std::string& title){
	this->title.set_markup(title);
	this->container.pack_start(this->title);
	this->container.pack_end(this->button);

	this->button.set_label("Seleccionar");
}

GameMenuField::~GameMenuField(){}

GameMenuField::GameMenuField(GameMenuField&& other): title(std::move(other.title)),
	button(std::move(other.button)), container(std::move(other.container)){}

Gtk::Container& GameMenuField::getContainer(){
	return this->container;
}

Gtk::Button& GameMenuField::getButton(){
	return this->button;
}