#ifndef __JOINGAMEMENU__
#define __JOINGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"
#include "GameMenuField.h"
#include "Player.h"
#include <string>
#include <memory>
#include <vector>

class JoinGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;
		Gtk::Box* games;
		std::vector<GameMenuField> game_fields;
		std::unique_ptr<Player> player;

		void configure(int quantity);

		void addGame(const std::string& game_name);

		void select_button_pressed(Glib::ustring game_name);

		void show_error();

	public:
		JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity);

		~JoinGameMenu();
};

#endif
