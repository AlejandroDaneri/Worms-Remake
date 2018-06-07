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

		void returnMenuButtonPressed();

		void quitButtonPressed();

	public:
		VictoryWindow(Gtk::Window& window);

		~VictoryWindow();

		void setWinner(const std::string& winner, bool i_win);
};


#endif //WORMS_VICTORYWINDOW_H
