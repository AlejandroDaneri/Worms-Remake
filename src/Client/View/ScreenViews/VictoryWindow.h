#ifndef WORMS_VICTORYWINDOW_H
#define WORMS_VICTORYWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <string>
#include "MenuView.h"

/* Clase que se encarga de mostrar una ventana con
 * un mensaje indicando el ganador de la partida cuando
 * esta finaliza. */
class VictoryWindow {
	private:
		Gtk::Window* my_window;
		Gtk::Window& window;
		Gtk::Button* return_menu;
		Gtk::Button* quit;
		Gtk::Label* victory_msg;
		MenuView& main_menu;
		bool was_closed;

		/* Handler de la ventana al cerrarse */
		bool on_delete_event(GdkEventAny* any_event);

		/* Handler del boton de retorno al menu */
		void returnMenuButtonPressed();

		/* Handler del boton salir */
		void quitButtonPressed();

	public:
		/* Constructor */
		VictoryWindow(Gtk::Window& window, MenuView& main_menu);

		/* Destructor */
		~VictoryWindow();


		/* Establece el mensaje del ganador y muestra la ventana
		 * con este mensaje y los botones */
		void setWinner(const std::string& winner, bool i_win);
};


#endif //WORMS_VICTORYWINDOW_H
