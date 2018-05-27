#ifndef __GAMEMENU__
#define __GAMEMENU__

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include "ClientProtocol.h"
#include "CreateGameMenu.h"
#include "JoinGameMenu.h"
#include <string>
#include <memory>

class GameMenu{
	private:
		Gtk::Window& window;
		ClientProtocol protocol;
		Gtk::Label* error;
		Gtk::Entry* player_name;
		std::unique_ptr<CreateGameMenu> create_menu;
		std::unique_ptr<JoinGameMenu> join_menu;

		void create_button_pressed();
		void join_button_pressed();

		bool select_action(char action);

	public:
		GameMenu(Gtk::Window& window, ClientProtocol&& protocol);

		~GameMenu();
};

#endif
