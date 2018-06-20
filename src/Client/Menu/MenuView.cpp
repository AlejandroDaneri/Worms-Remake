#include "MenuView.h"
#include <string>
#include "ServerFatalError.h"

MenuView::MenuView(Gtk::Window& window, MenuView& main_menu,
				   ClientProtocol& protocol, const std::string& path) :
		Menu(path, window), protocol(protocol), main_menu(main_menu) {}

MenuView::~MenuView() {
	delete this->menu;
}

void MenuView::showFatalError() {
	ServerFatalError error(this->window);
}

void MenuView::showErrorAndRestart(const std::string& error) {
	this->window.remove();
	this->main_menu.showError(error);
	this->window.add(*this->main_menu.menu);
}

void MenuView::addMenu(bool hide_error) {
	this->window.add(*this->menu);
	this->window.show_all();
	if (hide_error) {
		this->hideWarningBox();
	}
}
