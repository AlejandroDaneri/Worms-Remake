#ifndef __WORLDVIEW_H__
#define __WORLDVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/layout.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/scrolledwindow.h>
#include <string>
#include "Position.h"
#include "Water.h"

class Player;

/* Clase que se encarga de mostrar objetos en posiciones
 * especificas, moverlos y eliminarlos de la vista*/
class WorldView{
	private:
		Gtk::Layout world;
		Gtk::ScrolledWindow window;
		std::vector<Gtk::Image> background;
		Water water;

		bool setBackgroundImageCallBack(std::string image);

	public:
		/* Constructor */
		WorldView();

		/* Destructor */
		~WorldView();

		/* Setea la imagen de fondo */
		void setBackgroundImage(const std::string& image);

		/* Mueve el elemento pasado a la posicion especificada */
		void moveElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus = false);

		/* Mueve la mira a la posicion correspondiente para que tenga el angulo
		 * especificado por parametro */
		void moveScope(Gtk::Widget& scope, Gtk::Widget& worm, int angle);

		/* Remueve el elemento de la vista */
		void removeElement(Gtk::Widget& element);

		/* Agrega un elemento a la vista en la posicion especificada */
		void addElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus = false);

		/* Devuelve la vista del scrolledWindow */
		Gtk::ScrolledWindow& getWindow();

		/* Devuelve la vista del Layout */
		Gtk::Layout& getLayout();

		/* Realiza focus en el elemento pasado */
		void setFocus(Gtk::Widget& element);
};


#endif
