#ifndef __JOINGAMEMENU__
#define __JOINGAMEMENU__

#include <string>
#include "SelectableListMenu.h"

/* Clase que se encarga de los pasos necesarios para que el
 * jugador se una a una partida */
class JoinGameMenu : public SelectableListMenu {
private:
	/* Handler del boton de unirse a partida */
	void selectButtonPressed(Glib::ustring game_name) override;

public:
	/* Constructor */
	JoinGameMenu(Gtk::Window& window, MenuView& first_menu,
				 ClientProtocol& protocol, std::string&& name, int quantity);

	/* Destructor */
	~JoinGameMenu();
};

#endif
