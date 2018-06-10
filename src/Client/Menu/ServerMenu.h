#ifndef __SERVERMENU__
#define __SERVERMENU__

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <string>
#include <memory>
#include "ClientProtocol.h"
#include "GameMenu.h"
#include "MenuView.h"
#include "Menu.h"

/* Menu de conexion con el servidor */
class ServerMenu : public Menu {
private:
	Gtk::Entry* host;
	Gtk::Entry* service;
	Gtk::Button* connect;
	Gtk::Container* menu;
	std::unique_ptr<MenuView> next_menu;
	std::unique_ptr<ClientProtocol> protocol;

	/* Handler del boton de conexion */
	void connectButtonPressed();

	/* Intenta realizar una conexion con el servidor */
	void connectToServer(const std::string& host, const std::string& service);

public:
	/* Constructor */
	explicit ServerMenu(Gtk::Window& window);

	/* Destructor */
	~ServerMenu();
};

#endif
