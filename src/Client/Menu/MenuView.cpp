#include "MenuView.h"

MenuView::MenuView(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol):
	window(window), protocol(protocol), first_menu(first_menu){}

MenuView::~MenuView(){
	delete this->menu;
}

void MenuView::showFatalError(const std::string& error){
	this->error->set_label(error);
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}

void MenuView::showErrorAndRestart(const std::string& error){
	this->window.remove();
	this->first_menu.showError(error);
	this->window.add(*this->first_menu.menu);
}

void MenuView::showError(const std::string& error){
	this->error->set_label(error);
}
