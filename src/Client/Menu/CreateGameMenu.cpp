#include "CreateGameMenu.h"
#include <gtkmm/builder.h>
#include <glibmm/main.h>
#include "Path.h"
#include "GamePlayers.h"

#define MENU_WIDTH 936
#define MENU_HEIGHT 386

CreateGameMenu::CreateGameMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name, int quantity, Glib::RefPtr<Gtk::Application> app):
	SelectableListMenu(window, first_menu, protocol, std::move(name), app){

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_CreateGameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("game_name", this->game_name);
	builder->get_widget("players_number", this->players_number);
	builder->get_widget("games", this->games);
	builder->get_widget("quit_game", this->quit_game);

	this->configure(quantity);

	builder->get_widget("create_game_menu", this->menu);

	this->addMenu(MENU_WIDTH/2, MENU_HEIGHT/2);
	this->quit_game->signal_clicked().connect(sigc::mem_fun(*this, &CreateGameMenu::quitButtonPressed));
}

CreateGameMenu::~CreateGameMenu(){}

void CreateGameMenu::selectButtonPressed(Glib::ustring map_name){
	std::string name(this->game_name->get_text());
	if (name.empty()){
		this->error->set_label("Debe ingresar el nombre de la partida");
		return;
	}

	int players = this->players_number->get_value_as_int();
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
