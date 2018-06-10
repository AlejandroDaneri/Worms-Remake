#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <gtkmm/image.h>
#include "WorldView.h"
#include "WormView.h"

/* Clase que se encarga de controlar la imagen
 * de la mira del arma */
class Scope {
private:
	Gtk::Image scope;
	WorldView& world;
	int angle;

public:
	/* Constructor */
	explicit Scope(WorldView& world);

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
