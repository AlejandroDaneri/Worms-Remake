#include "JoinGameMenu.h"
#include "Path.h"
#include <gtkmm/builder.h>

JoinGameMenu::JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity):
	window(window), protocol(std::move(protocol)), player_name(std::move(player_name)){

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_JoinGameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("game", this->games);

	this->configure(quantity);

	Gtk::Box* menu;
	builder->get_widget("join_game_menu", menu);
	this->window.add(*menu);
	menu->show();
	}

JoinGameMenu::~JoinGameMenu(){}

void JoinGameMenu::configure(int quantity){
	for (int i = 0; i < quantity; i++){
		try{
			std::string game = this->protocol.receive_string();
			this->addGame(game);
		}catch (const SocketException& e){
			this->error->set_label("Ocurrio un error");
			this->show_error();
		}
	}
}

void JoinGameMenu::addGame(const std::string& game_name){
	GameMenuField game(game_name);
	this->game_fields.push_back(std::move(game));
	this->games->pack_start(this->game_fields.back().getContainer());
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
			this->player = std::unique_ptr<Player>(new Player(std::move(this->protocol), this->player_name));
			this->window.add(this->player->getWindow());
		}
	} catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->show_error();
	}
}

void JoinGameMenu::show_error(){
	this->window.remove();
	this->window.add(*this->error);
}
