#include "WaitingRoom.h"
#include "Path.h"
#include <string>

const std::string begining("<span size='20000'>");
const std::string ending("</span>");

#define SPACING 30

WaitingRoom::WaitingRoom(): container(true, SPACING){
	this->label.set_use_markup(true);
	this->label.set_markup(begining + "Esperando jugadores..." + ending);
	this->image.set(BACKGROUND_MENU_IMAGE);
	this->container.pack_start(this->image, Gtk::PACK_SHRINK);
	this->container.pack_start(this->label, Gtk::PACK_SHRINK);
	this->container.set_halign(Gtk::ALIGN_CENTER);
	this->container.set_valign(Gtk::ALIGN_CENTER);
}

WaitingRoom::~WaitingRoom() {}

Gtk::Widget& WaitingRoom::getWidget() {
	return this->container;
}
