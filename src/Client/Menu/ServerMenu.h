#ifndef __SERVERMENU__
#define __SERVERMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"
#include "GameMenu.h"
#include <string>
#include <memory>

class ServerMenu{
	private:
		Gtk::Label* error;
		Gtk::Entry* host;
		Gtk::Entry* service;
		Gtk::Button* connect;
		Gtk::Window& window;
		std::unique_ptr<GameMenu> game_menu;

		void connect_button_pressed();
		void connect_to_server(const std::string& host, const std::string& service);

	public:
		ServerMenu(Gtk::Window& window);

		~ServerMenu();
};

#endif
