#include "VictoryWindow.h"
#include <gtkmm/builder.h>
#include <string>
#include "Path.h"
#include "ButtonBuilder.h"

const std::string begining("<span color='black'");
const std::string medium(" font_family=\"monospace\" size='large'><b>");
const std::string end("</b></span>");

VictoryWindow::VictoryWindow(Gtk::Window& window, MenuView& main_menu) :
		window(window), main_menu(main_menu), was_closed(true) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(
			GLADE_PATH + "victory_window.glade");

	builder->get_widget("Menu", this->my_window);

	this->my_window->set_title(CLIENT_WINDOW_NAME);
	this->my_window->set_icon_from_file(ICON_PATH);

	builder->get_widget("victory_msg", victory_msg);
	this->victory_msg->set_use_markup(true);
	builder->get_widget("winner", winner);
	this->winner->set_use_markup(true);

	builder->get_widget("image", this->image);

	builder->get_widget("Return_menu", this->return_menu);
	builder->get_widget("quit", this->quit);

	ButtonBuilder::buildButton(this->quit);
	ButtonBuilder::buildButton(this->return_menu);

	this->return_menu->signal_clicked().connect(
			sigc::mem_fun(*this, &VictoryWindow::returnMenuButtonPressed));

	this->quit->signal_clicked().connect(
			sigc::mem_fun(*this, &VictoryWindow::quitButtonPressed));

	this->my_window->signal_delete_event().connect(
			sigc::mem_fun(*this, &VictoryWindow::on_delete_event));
}

VictoryWindow::~VictoryWindow() {}

bool VictoryWindow::on_delete_event(GdkEventAny* any_event) {
	gtk_widget_destroy((GtkWidget*) this->my_window->gobj());
	if (this->was_closed) {
		// Si se apreto el botón salir o el botón de cerrar
		this->window.close();
	}
	return true;
}

void VictoryWindow::returnMenuButtonPressed() {
	this->was_closed = false;
	this->my_window->close();
	this->window.remove();
	this->main_menu.addMenu();
}

void VictoryWindow::quitButtonPressed() {
	this->my_window->close();
}

void VictoryWindow::setWinner(const std::string& winner, bool i_win) {
	std::string victory_message = begining + medium;
	std::string winner_message = begining + medium;
	if (winner.empty()) {
		victory_message += "Empate";
		this->image->set(TIE_IMAGE);
	} else if (i_win) {
		victory_message += "GANASTE!!!!";
		this->image->set(WINNER_IMAGE);
	} else {
		victory_message += "Perdiste";
		winner_message +=  "El ganador fue: " + winner;
		this->image->set(LOSER_IMAGE);
	}
	victory_message += end;
	winner_message += end;
	this->victory_msg->set_markup(victory_message);
	this->winner->set_markup(winner_message);
	this->my_window->set_modal(true);
	this->my_window->show_all();
}
