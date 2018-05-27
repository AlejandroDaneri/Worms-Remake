#ifndef __SERVERMENU__
#define __SERVERMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"

class ServerMenu{
	private:
		Gtk::Label error;
		Gtk::HBox menu;
		Gtk::Entry host;
		Gtk::Entry service;
		Gtk::Button connect;
		Gtk::Window& window;

		void connect_button_pressed();

	public:
		ServerMenu(Gtk::Window& window);

		~ServerMenu();
};

#endif
