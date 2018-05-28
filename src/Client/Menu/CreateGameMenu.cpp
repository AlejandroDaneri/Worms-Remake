#include "CreateGameMenu.h"
#include "Path.h"
#include "GamePlayers.h"
#include <gtkmm/builder.h>
#include <glibmm/main.h>

CreateGameMenu::CreateGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity):
	window(window), protocol(std::move(protocol)), player_name(std::move(name)){

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_CreateGameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("game_name", this->game_name);
	builder->get_widget("players_number", this->players_number);
	builder->get_widget("games", this->games);

	this->configure(quantity);

	builder->get_widget("create_game_menu", this->menu);
	this->window.add(*this->menu);
	this->window.show_all();
}

CreateGameMenu::~CreateGameMenu(){}

void CreateGameMenu::configure(int quantity){
	try{
		for (int i = 0; i < quantity; i++){
			std::string map = this->protocol.receiveString();
			this->addMap(map);
		}
	}catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
	}

	for (auto it = this->maps.begin(); it != this->maps.end(); ++it){
		this->games->pack_start(it->getContainer());
	}
	this->games->show();
}

void CreateGameMenu::addMap(const std::string& map_name){
	GameMenuField map(map_name);
	this->maps.push_back(std::move(map));
	this->maps.back().getButton().signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &CreateGameMenu::select_button_pressed), map_name));
}

void CreateGameMenu::select_button_pressed(Glib::ustring map_name){
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
			this->error->set_label("Ocurrio un error al crear la partida");
			this->show_error();
		} else {
			this->window.remove();
			this->window.add(this->waiting_label.getWidget());
			this->window.show_all();
			sigc::slot<bool> my_slot = sigc::mem_fun(*this, &CreateGameMenu::createPlayer);
			Glib::signal_idle().connect(my_slot);
		}
	} catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
	}
}

void CreateGameMenu::show_error(){
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}

bool CreateGameMenu::createPlayer(){
	this->player = std::unique_ptr<Player>(new Player(std::move(this->protocol), this->player_name, this->window));
	return false;
}