#include "MenuView.h"

MenuView::MenuView(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol):
	window(window), protocol(protocol), first_menu(first_menu) {

	Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_from_file(BACKGROUND_MENU_IMAGE);
	this->background.set(aux);
	Glib::RefPtr<Gdk::Screen> screen = this->window.get_screen();
	int width = screen->get_width();
	int height = screen->get_height();

	this->world.put(this->background, width / 2 - aux->get_width() / 2,height / 2 - aux->get_height() / 2);
}

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
	this->window.add(this->first_menu.world);
}

void MenuView::showError(const std::string& error){
	this->error->set_label(error);
}
