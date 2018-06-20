#ifndef __VIEWABLE_H__
#define __VIEWABLE_H__

#include <gtkmm/widget.h>
#include "Position.h"
#include "Path.h"

class WorldView;

/* Clase que se encarga de controlar los objetos visuales */
class Viewable {
private:
	bool has_focus;

protected:
	WorldView& worldView;

	/* Agrega al objeto visual a la vista */
	void addToWorld(const Position& pos);

	/* Mueve al objeto visual a la posicion especificada */
	void move(const Position& pos);

public:
	/* Constructor */
	explicit Viewable(WorldView& worldView);

	/* Destructor */
	virtual ~Viewable();

	/* Constructor por movimiento */
	Viewable(Viewable&& other);

	/* Devuelve el contenedor del objeto visual */
	virtual Gtk::Widget& getWidget() = 0;

	/* Remueve al objeto visual de la vista */
	void removeFromWorld();

	/* Establece si al objeto visual se le puede hacer focus o no */
	void setFocus(bool focus);

	/* Devuelve true si el objeto visual es focuseable */
	bool hasFocus() const;

	/* Devuelve el ancho del viewable */
	virtual float getWidth() const = 0;

	/* Devuelve el alto del viewable */
	virtual float getHeight() const = 0;
};

#endif
