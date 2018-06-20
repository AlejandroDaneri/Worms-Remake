#ifndef __SCOPE_H__
#define __SCOPE_H__

#include <gtkmm/image.h>
#include "Viewable.h"
#include "WormView.h"

/* Clase que se encarga de controlar la imagen
 * de la mira del arma */
class Scope : public Viewable {
private:
	Gtk::Image scope;
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

	/* Devuelve el contenedor del scope */
	Gtk::Widget& getWidget() override;

	/* Devuelve el ancho del scope */
	float getWidth() const override;

	/* Devuelve el alto del scope */
	float getHeight() const override;
};

#endif
