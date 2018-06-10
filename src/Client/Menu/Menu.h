#ifndef WORMS_MENU_H
#define WORMS_MENU_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/builder.h>
#include <string>

class Menu {
protected:
	Gtk::Label* error;
	Gtk::Button* quit;
	Gtk::Window& window;
	Gtk::Image* title;
	Gtk::Image* background;
	Glib::RefPtr<Gtk::Builder> builder;

	/* Handler del boton de salir */
	void quitButtonPressed();

public:
	/* Constructor */
	Menu(const std::string& path, Gtk::Window& window);

	/* Destructor */
	~Menu();
};


#endif //WORMS_MENU_H
