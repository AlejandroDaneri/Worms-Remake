#include "ServerMenu.h"

ServerMenu::ServerMenu(Gtk::Window& window): window(window){
	this->menu.pack_start(this->error);
	this->menu.pack_start(this->host);
	this->menu.pack_start(this->service);
	this->menu.pack_start(this->connect);
	this->window.add(this->menu);
	this->menu.show();
}

ServerMenu::~ServerMenu(){}

void ServerMenu::connect_button_pressed(){

}