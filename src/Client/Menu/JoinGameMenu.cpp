#include "JoinGameMenu.h"
#include "Path.h"
#include "WaitingLabel.h"
#include <gtkmm/builder.h>
#include <glibmm/main.h>

JoinGameMenu::JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity):
	window(window), protocol(std::move(protocol)), player_name(std::move(name)){

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_JoinGameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("game", this->games);

	this->configure(quantity);

	builder->get_widget("join_game_menu", this->menu);
	this->window.add(*this->menu);
	this->window.show_all();
}

JoinGameMenu::~JoinGameMenu(){}

void JoinGameMenu::configure(int quantity){
	try{
		for (int i = 0; i < quantity; i++){
			std::string game = this->protocol.receive_string();
			this->addGame(game);
		}
	}catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
	}
	for (auto it = this->game_fields.begin(); it != this->game_fields.end(); ++it){
		this->games->pack_start(it->getContainer());
	}
	this->games->show();
}

void JoinGameMenu::addGame(const std::string& game_name){
	GameMenuField game(game_name);
	this->game_fields.push_back(std::move(game));
	this->game_fields.back().getButton().signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &JoinGameMenu::select_button_pressed), game_name));
}

void JoinGameMenu::select_button_pressed(Glib::ustring game_name){
	try{
		this->protocol.send_string(game_name);
		bool result = this->protocol.receive_char();
		if (!result){
			this->error->set_label("Ocurrio un error al unirse a la partida");
			this->show_error();
		} else {
			this->window.remove();
			this->window.add(this->waiting_label.getWidget());
			this->window.show_all();
			sigc::slot<bool> my_slot = sigc::mem_fun(*this, &JoinGameMenu::createPlayer);
			Glib::signal_idle().connect(my_slot);
		}
	} catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
	}
}

void JoinGameMenu::show_error(){
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}

bool JoinGameMenu::createPlayer(){
	this->player = std::unique_ptr<Player>(new Player(std::move(this->protocol), this->player_name, this->window));
	return false;
}
