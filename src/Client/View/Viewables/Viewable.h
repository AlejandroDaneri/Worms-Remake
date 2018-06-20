#ifndef __VIEWABLE_H__
#define __VIEWABLE_H__

#include <gtkmm/widget.h>
#include "WorldView.h"
#include "Position.h"
#include "Path.h"

/* Clase que se encarga de controlar los objetos visuales */
class Viewable {
private:
	WorldView& worldView;
	bool has_focus;

protected:
	/* Agrega al objeto visual a la vista */
	void addToWorld(const Position& pos, float width, float height);

	/* Mueve al objeto visual a la posicion especificada */
	void move(const Position& pos, float width, float height);

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
};

#endif