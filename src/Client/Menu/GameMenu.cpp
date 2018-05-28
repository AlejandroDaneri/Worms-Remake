#include "GameMenu.h"
#include "Path.h"
#include <gtkmm/builder.h>

GameMenu::GameMenu(Gtk::Window& window, ClientProtocol&& protocol): window(window), protocol(std::move(protocol)){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_GameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("player_name", this->player_name);

	builder->get_widget("game_menu", this->menu);
	this->window.add(*this->menu);
	this->menu->show();


	Gtk::Button *create_game, *join_game;
	builder->get_widget("create_game", create_game);
	builder->get_widget("join_game", join_game);
	create_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::create_button_pressed));
	join_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::join_button_pressed));
}

GameMenu::~GameMenu(){}

void GameMenu::create_button_pressed(){
	if (this->select_action(CREATE_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receive_length();
		if (quantity == 0){
			this->error->set_label("No hay mapas para crear una partida");
			this->show_error();
		} else {
			this->create_menu = std::unique_ptr<CreateGameMenu>(new CreateGameMenu(this->window, std::move(this->protocol), std::move(name), quantity));
		}
	}
}

void GameMenu::join_button_pressed(){
	if (this->select_action(JOIN_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receive_length();
		if (quantity == 0){
			this->error->set_label("No hay partidas disponibles");
			this->show_error();
		} else {
			this->join_menu = std::unique_ptr<JoinGameMenu>(new JoinGameMenu(this->window, std::move(this->protocol), std::move(name), quantity));
		}
	}
}

bool GameMenu::select_action(char action){
	std::string name(this->player_name->get_text());
	if (name.empty()){
		this->error->set_label("Debe ingresar su nombre");
		return false;
	}
	try{
		this->protocol.send_char(action);
		this->protocol.send_string(name);
		this->window.remove();
		return true;
	} catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
		return false;
	}
}

void GameMenu::show_error(){
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}
