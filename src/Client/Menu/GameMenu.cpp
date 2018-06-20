#include "GameMenu.h"
#include <string>
#include "Path.h"
#include "CreateGameMenu.h"
#include "JoinGameMenu.h"
#include "ButtonBuilder.h"

const std::string PATH = GLADE_PATH + "client_GameMenu.glade";

GameMenu::GameMenu(Gtk::Window& window, ClientProtocol& protocol) :
									MenuView(window, *this, protocol, PATH) {
	this->builder->get_widget("player_name", this->player_name);

	this->builder->get_widget("game_menu", this->menu);

	this->addMenu();

	Gtk::Button* create_game, * join_game;

	this->builder->get_widget("create_game", create_game);
	this->builder->get_widget("join_game", join_game);

	ButtonBuilder::buildButton(create_game);
	ButtonBuilder::buildButton(join_game);

	create_game->signal_clicked().connect(sigc::mem_fun(*this,
											&GameMenu::createButtonPressed));
	join_game->signal_clicked().connect(sigc::mem_fun(*this,
											&GameMenu::joinButtonPressed));
}

GameMenu::~GameMenu() {}

void GameMenu::createButtonPressed() {
	if (this->selectAction(CREATE_GAME_ACTION)) {
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0) {
			this->showErrorAndRestart("No hay mapas para crear una partida");
		} else {
			this->hideWarningBox();
			this->next_menu = std::unique_ptr<MenuView>(
					new CreateGameMenu(this->window, *this, this->protocol,
									   std::move(name), quantity));
		}
	}
}

void GameMenu::joinButtonPressed() {
	if (this->selectAction(JOIN_GAME_ACTION)) {
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0) {
			this->showErrorAndRestart("No hay partidas disponibles");
		} else {
			this->hideWarningBox();
			this->next_menu = std::unique_ptr<MenuView>(
					new JoinGameMenu(this->window, *this, this->protocol,
									 std::move(name), quantity));
		}
	}
}

bool GameMenu::selectAction(char action) {
	std::string name(this->player_name->get_text());
	if (name.empty()) {
		this->showError("Debe ingresar su nombre");
		return false;
	}
	try {
		this->protocol.sendChar(action);
		this->protocol.sendString(name);
		this->window.remove();
		return true;
	} catch(const SocketException& e) {
		this->showFatalError();
		return false;
	}
}
