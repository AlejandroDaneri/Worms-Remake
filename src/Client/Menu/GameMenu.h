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
		void create_button_pressed();

		/* Crea el boton de unirse a partida */
		void join_button_pressed();

		/* Envia la accion implementada */
		bool select_action(char action);

		/* Muestra un mensaje de error */
		void show_error();

	public:
		/* Constructor */
		GameMenu(Gtk::Window& window, ClientProtocol&& protocol);

		/* Destructor */
		~GameMenu();
};

#endif
