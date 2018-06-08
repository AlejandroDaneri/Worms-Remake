#include "VictoryWindow.h"
#include <gtkmm/builder.h>
#include "Path.h"
#include <iostream>

VictoryWindow::VictoryWindow(Gtk::Window& window, MenuView& main_menu) :
	window(window), main_menu(main_menu) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "victory_window.glade");

	builder->get_widget("Menu", this->my_window);

	this->my_window->set_title(CLIENT_WINDOW_NAME);
	this->my_window->set_icon_from_file(ICON_PATH);

	builder->get_widget("victory_msg", victory_msg);

	builder->get_widget("Return_menu", this->return_menu);
	builder->get_widget("quit", this->quit);

	this->return_menu->signal_clicked().connect(sigc::mem_fun(*this, &VictoryWindow::returnMenuButtonPressed));

	this->quit->signal_clicked().connect(sigc::mem_fun(*this, &VictoryWindow::quitButtonPressed));
}

VictoryWindow::~VictoryWindow() {}

void VictoryWindow::returnMenuButtonPressed() {
	this->my_window->close();
	this->window.remove();
	this->main_menu.addMenu();
}

void VictoryWindow::quitButtonPressed() {
	this->my_window->close();
	this->window.close();
}

void VictoryWindow::setWinner(const std::string& winner, bool i_win) {
	std::string winner_message;
	if (winner.empty()){
		winner_message = "Empate";
	} else if (i_win) {
		winner_message = "GANASTE!!!!";
	} else {
		winner_message = "Perdiste. El ganador fue: " + winner;
	}
	this->victory_msg->set_text(winner_message);
	this->my_window->set_modal(true);
	this->my_window->set_deletable(false);
	this->my_window->show_all();
}
