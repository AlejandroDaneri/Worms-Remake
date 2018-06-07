#ifndef __MENUVIEW_H__
#define __MENUVIEW_H__

#include <gtkmm/container.h>
#include <memory>
#include "ClientProtocol.h"
#include "Menu.h"

class MenuView : public Menu {
	private:
		/* Muestra un mensaje de error */
		void showError(const std::string& error);

	protected:
		ClientProtocol& protocol;
		std::unique_ptr<MenuView> next_menu;
		MenuView& main_menu;
		Gtk::Container* menu;

		/* Muestra un mensaje de error y cierra la aplicacion*/
		void showFatalError();

		/* Muestra un mensaje de error y reinicia */
		void showErrorAndRestart(const std::string& error);

		/* Agrega el menu al world y el world al window */
		void addMenu();

	public:
		/* Constructor */
		MenuView(Gtk::Window& window, MenuView& main_menu, ClientProtocol& protocol, const std::string& path);

		/* Destructor */
		virtual ~MenuView();
};

#endif
