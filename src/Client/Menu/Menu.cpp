#include "Menu.h"
#include <string>
#include "Path.h"
#include "ButtonBuilder.h"

Menu::Menu(const std::string& path, Gtk::Window& window) : window(window) {
	this->builder = Gtk::Builder::create_from_file(path);

	this->builder->get_widget("error", this->error);

	this->builder->get_widget("quit_game", this->quit);

	ButtonBuilder::buildButton(this->quit);

	this->builder->get_widget("title", this->title);
	this->title->set(TITLE_MENU_IMAGE);

	this->builder->get_widget("background", this->background);
	this->background->set(BACKGROUND_MENU_IMAGE);

	this->quit->signal_clicked().connect(
			sigc::mem_fun(*this, &Menu::quitButtonPressed));
}

Menu::~Menu() {}

void Menu::quitButtonPressed() {
	this->window.close();
}
