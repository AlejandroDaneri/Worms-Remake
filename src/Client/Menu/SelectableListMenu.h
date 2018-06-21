#ifndef __SELECTABLELISTMENU_H__
#define __SELECTABLELISTMENU_H__

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <memory>
#include <string>
#include <vector>
#include "ClientProtocol.h"
#include "MenuView.h"
#include "WaitingRoom.h"
#include "Player.h"
#include "GameMenuField.h"

class SelectableListMenu : public MenuView {
protected:
	Gtk::Box* games;
	std::string player_name;
	WaitingRoom waiting_room;
	std::vector<GameMenuField> fields;
	std::unique_ptr<Player> player;
	Gtk::Button* turn_back;

	/* Realiza la configuracion del juego */
	void configure(int quantity);

	/* Agrega un campo a la lista */
	void addField(const std::string& field_name);

	/* Crea un nuevo jugador */
	bool createPlayer();

	/* Handler del boton de seleccion */
	virtual void selectButtonPressed(Glib::ustring field_name) = 0;

	/* Handler del boton volver */
	void turnBackButtonPressed();

	/* Muestra el mensaje esperando jugadores */
	void waitToPlayers();

public:
	/* Constructor */
	SelectableListMenu(Gtk::Window& window, MenuView& first_menu,
					   ClientProtocol& protocol, std::string&& name,
					   const std::string& path);

	/* Destructor */
	~SelectableListMenu();
};

#endif
