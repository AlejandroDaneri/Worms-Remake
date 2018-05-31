#include "JoinGameMenu.h"
#include <gtkmm/builder.h>
#include <glibmm/main.h>
#include "Path.h"
#include "WaitingLabel.h"

#define MENU_WIDTH 144
#define MENU_HEIGHT 142

JoinGameMenu::JoinGameMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name, int quantity):
	SelectableListMenu(window, first_menu, protocol, std::move(name)){

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_JoinGameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("game", this->games);

	this->configure(quantity);

	builder->get_widget("join_game_menu", this->menu);

	Glib::RefPtr<Gdk::Screen> screen = this->window.get_screen();

	this->world.put(*this->menu, screen->get_width() / 2 - MENU_WIDTH/2, screen->get_height() / 2 - MENU_HEIGHT/2);

	this->window.add(this->world);
	this->window.show_all();
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
