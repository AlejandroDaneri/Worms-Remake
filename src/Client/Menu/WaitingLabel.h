#ifndef __WAITINGLABEL_H__
#define __WAITINGLABEL_H__

#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/hvbox.h>

/* Label de que indica la espera a otros jugadores */
class WaitingLabel {
private:
	Gtk::VBox container;
	Gtk::Label label;
	Gtk::Image image;

public:
	/* Constructor */
	WaitingLabel();

	/* Destructor */
	~WaitingLabel();

	/* Devuelve el contenedor del mensaje */
	Gtk::Widget& getWidget();
};


#endif
