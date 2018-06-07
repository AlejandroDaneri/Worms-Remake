#ifndef WORMS_VICTORYWINDOW_H
#define WORMS_VICTORYWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <string>

class VictoryWindow {
	private:
		Gtk::Window* my_window;
		Gtk::Window& window;
		Gtk::Button* return_menu;
		Gtk::Button* quit;
		Gtk::Label* victory_msg;
		std::string winner_msg;
		bool made_choice;

		void returnMenuButtonPressed();

		void quitButtonPressed();

	public:
		VictoryWindow(Gtk::Window& window);

		~VictoryWindow();

		void setWinner(std::string&& message);

		void show_all();
};


#endif //WORMS_VICTORYWINDOW_H
