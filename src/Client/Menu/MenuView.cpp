#include "MenuView.h"
#include "ServerFatalError.h"

MenuView::MenuView(Gtk::Window& window, MenuView& main_menu, ClientProtocol& protocol):
	window(window), protocol(protocol), main_menu(main_menu) {

	Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_from_file(BACKGROUND_MENU_IMAGE);
	this->background.set(aux);
	this->menu_container.add_overlay(this->background);
}

MenuView::~MenuView(){
	delete this->menu;
}

void MenuView::showFatalError(){
	ServerFatalError error(this->window);
}

void MenuView::showErrorAndRestart(const std::string& error){
	this->window.remove();
	this->main_menu.showError(error);
	this->window.add(this->main_menu.menu_container);
}

void MenuView::showError(const std::string& error){
	this->error->set_label(error);
}

void MenuView::quitButtonPressed() {
	this->window.close();
}

void MenuView::addMenu() {
	this->menu_container.add_overlay(*this->menu);
	this->window.add(this->menu_container);
	this->window.show_all();
}
