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

	this->builder->get_widget("warning1", this->warning1);
	this->warning1->set(WARNING_IMAGE);

	this->builder->get_widget("warning2", this->warning2);
	this->warning2->set(WARNING_IMAGE);

	this->quit->signal_clicked().connect(
			sigc::mem_fun(*this, &Menu::quitButtonPressed));

	this->builder->get_widget("warning_box", this->warning_box);
}

Menu::~Menu() {}

void Menu::quitButtonPressed() {
	this->window.close();
}

void Menu::hideWarningBox() {
	this->error->hide();
	this->warning1->hide();
	this->warning2->hide();
}

void Menu::showError(const std::string& error) {
	if (error.empty()) {
		this->hideWarningBox();
	} else {
		this->error->set_label(error);
		this->warning_box->show_all();
	}
}
