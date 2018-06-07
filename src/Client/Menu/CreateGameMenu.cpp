#include "CreateGameMenu.h"
#include "Path.h"
#include "GamePlayers.h"

const std::string PATH = GLADE_PATH + "client_CreateGameMenu.glade";

CreateGameMenu::CreateGameMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name, int quantity):
	SelectableListMenu(window, first_menu, protocol, std::move(name), PATH){

	this->builder->get_widget("game_name", this->game_name);
	this->builder->get_widget("players_number", this->players_number);
	this->builder->get_widget("games", this->games);

	this->configure(quantity);

	this->builder->get_widget("create_game_menu", this->menu);

	this->addMenu();
}

CreateGameMenu::~CreateGameMenu(){}

void CreateGameMenu::selectButtonPressed(Glib::ustring map_name){
	std::string name(this->game_name->get_text());
	if (name.empty()){
		this->error->set_label("Debe ingresar el nombre de la partida");
		return;
	}

	size_t players = this->players_number->get_value_as_int();
	if (players < min_players || players > max_players){
		std::string message("El numero de jugadores debe estar entre ");
		message += std::to_string(min_players) + std::string(" y ") + std::to_string(max_players);
		this->error->set_label(message);
		return;
	}

	try{
		this->protocol.sendString(map_name);
		this->protocol.sendString(name);
        this->protocol.sendLength(players);
		bool result = this->protocol.receiveChar();
		if (!result){
            this->showErrorAndRestart("Ocurrio un error al crear la partida");
		} else {
			this->waitToPlayers();
		}
	} catch (const SocketException& e){
        this->showFatalError();
	}
}
