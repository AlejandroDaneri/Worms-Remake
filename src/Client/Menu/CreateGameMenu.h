#ifndef __CREATEGAMEMENU__
#define __CREATEGAMEMENU__

#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include "SelectableListMenu.h"

/* Clase que se encarga de los pasos necesarios para que el
 * jugador cree una partida */
class CreateGameMenu: public SelectableListMenu{
	private:
		Gtk::Entry* game_name;
		Gtk::SpinButton* players_number;

		/* Handler del boton de seleccion */
		void selectButtonPressed(Glib::ustring map_name) override;

	public:
        /* Constructor */
		CreateGameMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name, int quantity);

		/* Destructor */
		~CreateGameMenu();
};

#endif
