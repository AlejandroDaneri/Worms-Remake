#include "GameMenu.h"
#include <gtkmm/builder.h>
#include "Path.h"
#include "CreateGameMenu.h"
#include "JoinGameMenu.h"

#define MENU_WIDTH 918
#define MENU_HEIGHT 570

GameMenu::GameMenu(Gtk::Window& window, ClientProtocol& protocol):
	MenuView(window, *this, protocol){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_GameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("player_name", this->player_name);

	builder->get_widget("game_menu", this->menu);

	this->addMenu(MENU_WIDTH/2, MENU_HEIGHT/2);

	Gtk::Button *create_game, *join_game, *quit_game;

	builder->get_widget("create_game", create_game);
	builder->get_widget("join_game", join_game);
	builder->get_widget("quit_game", quit_game);

	create_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::createButtonPressed));
	join_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::joinButtonPressed));
	quit_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::quitButtonPressed));
}

GameMenu::~GameMenu(){}

void GameMenu::createButtonPressed(){
	if (this->selectAction(CREATE_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0){
			this->showErrorAndRestart("No hay mapas para crear una partida");
		} else {
			this->next_menu = std::unique_ptr<MenuView>(new CreateGameMenu(this->window, *this, this->protocol, std::move(name), quantity));
		}
	}
}

void GameMenu::joinButtonPressed(){
	if (this->selectAction(JOIN_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0){
			this->showErrorAndRestart("No hay partidas disponibles");
		} else {
			this->next_menu = std::unique_ptr<MenuView>(new JoinGameMenu(this->window, *this, this->protocol, std::move(name), quantity));
		}
	}
}

bool GameMenu::selectAction(char action){
	std::string name(this->player_name->get_text());
	if (name.empty()){
		this->error->set_label("Debe ingresar su nombre");
		return false;
	}
	try{
		this->protocol.sendChar(action);
		this->protocol.sendString(name);
		this->window.remove();
		return true;
	} catch (const SocketException& e){
		this->showFatalError();
		return false;
	}
}
