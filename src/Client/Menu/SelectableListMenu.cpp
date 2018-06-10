#include "SelectableListMenu.h"
#include <string>
#include "ButtonBuilder.h"

SelectableListMenu::SelectableListMenu(Gtk::Window& window,
									   MenuView& first_menu,
									   ClientProtocol& protocol,
									   std::string&& name,
									   const std::string& path) :
		MenuView(window, first_menu, protocol, path),
		player_name(std::move(name)) {
	this->builder->get_widget("turn_back", this->turn_back);
	ButtonBuilder::buildButton(this->turn_back);
	this->turn_back->signal_clicked().connect(
			sigc::mem_fun(*this, &SelectableListMenu::turnBackButtonPressed));
}

SelectableListMenu::~SelectableListMenu() {}

void SelectableListMenu::turnBackButtonPressed() {
	std::string string;
	try {
		this->protocol.sendString(string);
		this->showErrorAndRestart(string);
	} catch(const std::exception& e) {
		this->showFatalError();
	}
}

void SelectableListMenu::configure(int quantity) {
	try {
		for (int i = 0; i < quantity; i++) {
			std::string field = this->protocol.receiveString();
			this->addField(field);
		}
	} catch(const SocketException& e) {
		this->showFatalError();
	}

	for (auto it = this->fields.begin(); it != this->fields.end(); ++it) {
		this->games->pack_start(it->getContainer());
	}
	this->games->show();
}

void SelectableListMenu::addField(const std::string& field_name) {
	GameMenuField field(field_name);
	this->fields.push_back(std::move(field));
	this->fields.back().getButton().signal_clicked().connect(
			sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
						&SelectableListMenu::selectButtonPressed), field_name));
}

bool SelectableListMenu::createPlayer() {
	try {
		this->player = std::unique_ptr<Player>(
				new Player(this->protocol, this->player_name, this->window,
						   this->main_menu));
	} catch(const std::exception& e) {
		this->showFatalError();
	}
	return false;
}

void SelectableListMenu::waitToPlayers() {
	this->window.remove();
	this->window.add(this->waiting_label.getWidget());
	this->window.show_all();
	sigc::slot<bool> my_slot = sigc::mem_fun(*this,
											 &SelectableListMenu::createPlayer);
	Glib::signal_idle().connect(my_slot);
}
