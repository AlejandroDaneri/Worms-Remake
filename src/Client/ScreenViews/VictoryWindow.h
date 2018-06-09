#ifndef WORMS_VICTORYWINDOW_H
#define WORMS_VICTORYWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <string>
#include "MenuView.h"

class Player;

class VictoryWindow {
	private:
		Gtk::Window* my_window;
		Gtk::Window& window;
		Gtk::Button* return_menu;
		Gtk::Button* quit;
		Gtk::Label* victory_msg;
		MenuView& main_menu;
		Player& player;
		bool was_closed;

		bool on_delete_event(GdkEventAny* any_event);

		void returnMenuButtonPressed();

		void quitButtonPressed();

	public:
		VictoryWindow(Gtk::Window& window, MenuView& main_menu, Player& player);

		~VictoryWindow();

		void setWinner(const std::string& winner, bool i_win);
};


#endif //WORMS_VICTORYWINDOW_H
