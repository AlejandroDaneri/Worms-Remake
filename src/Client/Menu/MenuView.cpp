#include "MenuView.h"

MenuView::MenuView(Gtk::Window& window, ClientProtocol&& protocol):
	window(window), protocol(std::move(protocol)){}

MenuView::~MenuView(){}

void MenuView::showError(const std::string& error){
	this->error->set_label(error);
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}