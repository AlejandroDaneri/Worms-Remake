#include "MenuView.h"

MenuView::MenuView(Gtk::Window& window, ClientProtocol&& protocol):
	window(window), protocol(std::move(protocol)){}

MenuView::~MenuView(){}

void MenuView::showError(){
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}