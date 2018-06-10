#ifndef __WINDVIEW_H__
#define __WINDVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>


/* Clase que se encarga de mostrar y actualizar
 * la informacion del viento */
class WindView {
private:
	Gtk::VBox container;
	Gtk::Label velocity;
	Gtk::Image direction;

public:
	/* Constructor */
	WindView();

	/* Destructor */
	~WindView();

	/* Actualiza la vista del viento */
	void update(float wind);

	/* Devuelve el contenedor del viento */
	Gtk::VBox& getWindow();
};

#endif

