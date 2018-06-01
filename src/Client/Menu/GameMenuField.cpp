#include "GameMenuField.h"
#include <gdkmm/rgba.h>
#include "Path.h"
#include "ButtonBuilder.h"

GameMenuField::GameMenuField(const std::string& title): container(true, 20){
	size_t extension = title.rfind(YAML_EXTENSION);
	this->title.set_markup(title.substr(0, extension));
	this->title.override_color(Gdk::RGBA("black"));
	this->title.override_background_color(Gdk::RGBA("white"));
	this->container.pack_start(this->title);
	this->container.pack_end(this->button);

	this->button.set_label("Seleccionar");
	ButtonBuilder::buildButton(&this->button);
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
