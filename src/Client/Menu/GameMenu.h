#ifndef __GAMEMENU__
#define __GAMEMENU__

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <string>
#include <memory>
#include "ClientProtocol.h"
#include "MenuView.h"

/* Clase que se encarga de controlar el menu del juego */
class GameMenu: public MenuView{
	private:
		Gtk::Entry* player_name;

		/* Crea el boton de creacion de partida */
		void createButtonPressed();

		/* Crea el boton de unirse a partida */
		void joinButtonPressed();

		/* Envia la accion implementada */
		bool selectAction(char action);

	public:
		/* Constructor */
		GameMenu(Gtk::Window& window, ClientProtocol&& protocol);

		/* Destructor */
		~GameMenu();
};

#endif
