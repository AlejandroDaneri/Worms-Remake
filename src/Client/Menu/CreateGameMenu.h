#ifndef __CREATEGAMEMENU__
#define __CREATEGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include <string>
#include <memory>
#include <vector>
#include "ClientProtocol.h"
#include "GameMenuField.h"
#include "WaitingLabel.h"
#include "Player.h"

/* Clase que se encarga de los pasos necesarios para que el
 * jugador cree una partida */
class CreateGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;
		Gtk::Entry* game_name;
		Gtk::SpinButton* players_number;
		Gtk::Box* games;
		Gtk::Box* menu;
		std::vector<GameMenuField> maps;
		std::unique_ptr<Player> player;
		WaitingLabel waiting_label;

		/* Realiza la configuracion del juego */
		void configure(int quantity);

		/* Agrega un mapa a la lista de mapas */
		void addMap(const std::string& map_name);

		/* Handler del boton de seleccion */
		void select_button_pressed(Glib::ustring map_name);

		/* Muestra un mensaje de error */
		void show_error();

		/* Crea un nuevo jugador */
		bool createPlayer();

	public:
        /* Constructor */
		CreateGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity);

		/* Destructor */
		~CreateGameMenu();
};

#endif
