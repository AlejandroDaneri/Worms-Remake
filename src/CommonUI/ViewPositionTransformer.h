#ifndef __VIEWTRANSFORMER_H__
#define __VIEWTRANSFORMER_H__

#include <gtkmm/layout.h>
#include "Position.h"

/* Clase que se encarga de transformar posiciones de la pantalla
 * en posiciones en metros */
class ViewPositionTransformer{
	private:
		Gtk::Layout& layout;

	public:
		/* Constructor */
		explicit ViewPositionTransformer(Gtk::Layout& layout);

		/* Destructor */
		~ViewPositionTransformer();

		/* Dada una posicion en metros, devuelve una posicion en
		 * pixeles que representa una posicion de la pantalla*/
		Position transformToScreen(const Position& position);

		/* Dada una posicion en metros, la transforma en una posicion
		 * para la pantalla y la desplaza segun su ancho y alto */
		Position transformToScreenAndMove(const Position& pos, float w, float h);

		/* Dada una posicion en pixeles, devuelve una posicion en metros */
		Position transformToPosition(const Position& position);
};

#endif
