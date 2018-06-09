#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <gtkmm/image.h>
#include "WorldView.h"
#include "WormView.h"

class Scope{
	private:
		Gtk::Image scope;
		WorldView& world;
		int angle;

	public:
		/* Constructor */
		Scope(WorldView& world);

		/* Destructor */
		~Scope();

		/* Actualiza la posicion del scope */
		void update(int angle, WormView& worm);

		/* Actualiza la posicion del scope */
		void update(WormView& worm);

		/* Esconde el scope */
		void hide();

};

#endif
