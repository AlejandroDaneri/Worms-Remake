#ifndef __GAMEMENU__
#define __GAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>
#include <memory>
#include "ClientProtocol.h"
#include "CreateGameMenu.h"
#include "JoinGameMenu.h"

/* Clase que se encarga de controlar el menu del juego */
class GameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		Gtk::Label* error;
		Gtk::Entry* player_name;
		std::unique_ptr<CreateGameMenu> create_menu;
		std::unique_ptr<JoinGameMenu> join_menu;
		Gtk::Box* menu;

		/* Crea el boton de creacion de partida */
		void createButtonPressed();

		/* Crea el boton de unirse a partida */
		void joinButtonPressed();

		/* Envia la accion implementada */
		bool selectAction(char action);

		/* Muestra un mensaje de error */
		void showError();

	public:
		/* Constructor */
		GameMenu(Gtk::Window& window, ClientProtocol&& protocol);

		/* Destructor */
		~GameMenu();
};

#endif
