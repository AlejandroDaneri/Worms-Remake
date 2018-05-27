#ifndef __JOINGAMEMENU__
#define __JOINGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"
#include <string>
#include <memory>

class JoinGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;

	public:
		JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity);

		~JoinGameMenu();
};

#endif
