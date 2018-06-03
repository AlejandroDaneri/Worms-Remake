#ifndef __SERVERMENU__
#define __SERVERMENU__

#include <gtkmm/application.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/overlay.h>
#include <gtkmm/image.h>
#include <string>
#include <memory>
#include "ClientProtocol.h"
#include "GameMenu.h"
#include "MenuView.h"

/* Menu de conexion con el servidor */
class ServerMenu{
	private:
		Gtk::Label* error;
		Gtk::Entry* host;
		Gtk::Entry* service;
		Gtk::Button* connect;
		Gtk::Button* quit;
		Gtk::Window& window;
		Gtk::Box* menu;
		std::unique_ptr<MenuView> next_menu;
		std::unique_ptr<ClientProtocol> protocol;

		Gtk::Overlay* menu_container;
		Gtk::Image* background;

		/* Handler del boton de conexion */
		void connectButtonPressed();

		/* Handler del boton de salir */
		void quitButtonPressed();

		/* Intenta realizar una conexion con el servidor */
		void connectToServer(const std::string &host, const std::string &service);

	public:
        /* Constructor */
		ServerMenu(Gtk::Window& window);

		/* Destructor */
		~ServerMenu();
};

#endif
