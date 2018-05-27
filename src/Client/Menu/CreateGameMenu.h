#ifndef __CREATEGAMEMENU__
#define __CREATEGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"
#include <string>
#include <memory>

class CreateGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;

	public:
		CreateGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name);

		~CreateGameMenu();
};

#endif
