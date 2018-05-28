#ifndef __JOINGAMEMENU__
#define __JOINGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>
#include <memory>
#include <vector>
#include "ClientProtocol.h"
#include "GameMenuField.h"
#include "WaitingLabel.h"
#include "Player.h"

/* Clase que se encarga de los pasos necesarios para que el
 * jugador se una a una partida */
class JoinGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;
		Gtk::Box* games;
		std::vector<GameMenuField> game_fields;
		std::unique_ptr<Player> player;
		Gtk::Box* menu;
		WaitingLabel waiting_label;

		/* Realiza la configuracion del juego */
		void configure(int quantity);

		/* Agrega el nombre del juego */
		void addGame(const std::string& game_name);

		/* Handler del boton de unirse a partida */
		void selectButtonPressed(Glib::ustring game_name);

		/* Muestra un mensaje de error */
		void showError();

		/* Crea un nuevo jugador */
		bool createPlayer();

	public:
		/* Constructor */
		JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity);

		/* Destructor */
		~JoinGameMenu();
};

#endif
