#ifndef __SERVERMENU__
#define __SERVERMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>
#include <memory>
#include "ClientProtocol.h"
#include "GameMenu.h"

class ServerMenu{
	private:
		Gtk::Label* error;
		Gtk::Entry* host;
		Gtk::Entry* service;
		Gtk::Button* connect;
		Gtk::Window& window;
		std::unique_ptr<GameMenu> game_menu;

		/* Handler del boton de conexion */
		void connect_button_pressed();

		/* Intenta realizar una conexion con el servidor */
		void connect_to_server(const std::string& host, const std::string& service);

	public:
        /* Constructor */
		ServerMenu(Gtk::Window& window);

		/* Destructor */
		~ServerMenu();
};

#endif
