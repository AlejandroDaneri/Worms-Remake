#ifndef __GAMEMENUFIELD_H__
#define __GAMEMENUFIELD_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <string>

class GameMenuField{
	private:
		Gtk::Label title;
		Gtk::Button button;
		Gtk::HBox container;

	public:
		/* Constructor */
		GameMenuField(const std::string& title);

		/* Destructor */
		~GameMenuField();

		/* Constructor por movimiento */
		GameMenuField(GameMenuField&& other);


		/* Devuelve el contenedor del menu */
		Gtk::Container& getContainer();

		/* Devuelve el boton del menu */
		Gtk::Button& getButton();
};


#endif
