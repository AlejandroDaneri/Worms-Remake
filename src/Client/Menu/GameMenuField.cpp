#include "GameMenuField.h"
#include "Path.h"

GameMenuField::GameMenuField(const std::string& title): container(true, 20){
	size_t extension = title.rfind(YAML_EXTENSION);
	this->title.set_markup(title.substr(0, extension));
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