#ifndef __CREATEGAMEMENU__
#define __CREATEGAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include "ClientProtocol.h"
#include "GameMenuField.h"
#include "WaitingLabel.h"
#include "Player.h"
#include <string>
#include <memory>
#include <vector>

class CreateGameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		std::string player_name;
		Gtk::Label* error;
		Gtk::Entry* game_name;
		Gtk::SpinButton* players_number;
		Gtk::Box* games;
		Gtk::Box* menu;
		std::vector<GameMenuField> maps;
		std::unique_ptr<Player> player;
		WaitingLabel waiting_label;

		void configure(int quantity);

		void addMap(const std::string& map_name);

		void select_button_pressed(Glib::ustring map_name);

		void show_error();

		bool createPlayer();

	public:
		CreateGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity);

		~CreateGameMenu();
};

#endif
