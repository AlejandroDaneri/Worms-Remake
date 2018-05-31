#ifndef __MENUVIEW_H__
#define __MENUVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <memory>
#include "ClientProtocol.h"

class MenuView{
	protected:
		Gtk::Window& window;
		ClientProtocol& protocol;
		Gtk::Label* error;
		std::unique_ptr<MenuView> next_menu;
		MenuView& first_menu;
		Gtk::Box* menu;

		/* Muestra un mensaje de error */
		void showError(const std::string& error = "Ocurrio un error.");

	public:
		/* Constructor */
		MenuView(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol);

		/* Destructor */
		virtual ~MenuView();
};

#endif
