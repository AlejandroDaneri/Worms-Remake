#ifndef __VIEWTRANSFORMER_H__
#define __VIEWTRANSFORMER_H__

#include <gtkmm/layout.h>
#include "Position.h"

/* Clase que se encarga de transformar posiciones de la pantalla
 * en posiciones en metros */
class ViewTransformer{
	private:
		Gtk::Layout& layout;

	public:
		/* Constructor */
		ViewTransformer(Gtk::Layout& layout);

		/* Destructor */
		~ViewTransformer();


		/* Dada una posicion en metros, devuelve una posicion en
		 * pixeles que representa una posicion de la pantalla*/
		Position transformToScreen(const Position& position);

		/* Dada una posicion en metros, la transforma en una posicion
		 * para la pantalla y la desplaza */
		Position transformToScreenAndMove(const Position& position, float width, float height);

		/* Dada una posicion en pixeles, devuelve una posicion en metros */
		Position transformToPosition(const Position& position);
};

#endif
