#ifndef __MENUVIEW_H__
#define __MENUVIEW_H__

#include <gtkmm/container.h>
#include <memory>
#include <string>
#include "ClientProtocol.h"
#include "Menu.h"

class MenuView : public Menu {
protected:
	std::unique_ptr<MenuView> next_menu;
	ClientProtocol& protocol;
	MenuView& main_menu;
	Gtk::Container* menu;

	/* Muestra un mensaje de error y cierra la aplicacion*/
	void showFatalError();

	/* Muestra un mensaje de error y reinicia */
	void showErrorAndRestart(const std::string& error);

public:
	/* Constructor */
	MenuView(Gtk::Window& window, MenuView& main_menu, ClientProtocol& protocol,
			 const std::string& path);

	/* Destructor */
	virtual ~MenuView();

	/* Agrega el menu al container y el container al window */
	void addMenu(bool hide_error);
};

#endif
