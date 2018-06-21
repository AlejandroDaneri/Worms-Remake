#ifndef __WAITINGLABEL_H__
#define __WAITINGLABEL_H__

#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/hvbox.h>

/* Label de que indica la espera a otros jugadores */
class WaitingRoom {
private:
	Gtk::VBox container;
	Gtk::Label label;
	Gtk::Image image;

public:
	/* Constructor */
	WaitingRoom();

	/* Destructor */
	~WaitingRoom();

	/* Devuelve el contenedor del mensaje */
	Gtk::Widget& getWidget();
};


#endif
