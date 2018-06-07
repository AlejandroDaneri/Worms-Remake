#include "JoinGameMenu.h"
#include "Path.h"
#include "WaitingLabel.h"

const std::string PATH = GLADE_PATH + "client_JoinGameMenu.glade";

JoinGameMenu::JoinGameMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name, int quantity):
	SelectableListMenu(window, first_menu, protocol, std::move(name), PATH){

	this->builder->get_widget("games", this->games);

	this->configure(quantity);

	this->builder->get_widget("join_game_menu", this->menu);

	this->addMenu();
}

JoinGameMenu::~JoinGameMenu(){}


void JoinGameMenu::selectButtonPressed(Glib::ustring game_name){
	try{
		this->protocol.sendString(game_name);
		bool result = this->protocol.receiveChar();
		if (!result){
            this->showErrorAndRestart("Ocurrio un error al unirse a la partida");
		} else {
			this->waitToPlayers();
		}
	} catch (const SocketException& e){
        this->showFatalError();
	}
}
