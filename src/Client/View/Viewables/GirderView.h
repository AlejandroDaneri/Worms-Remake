#ifndef __GIRDERVIEW_H__
#define __GIRDERVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>
#include "Viewable.h"

/* Clase que se encaga de controlar la vista de las vigas */
class GirderView : public Viewable {
private:
	Gtk::Image image;
	int size;
	int rotation;

public:
	/* Constructor */
	GirderView(WorldView& worldView, size_t size, Position pos, int rotation);

	/* Destructor */
	~GirderView();

	/* Constructor por movimiento */
	GirderView(GirderView&& other);

	/* Devuelve el contenedor de la viga */
	Gtk::Widget& getWidget() override;

	/* Devuelve el ancho de la viga */
	float getWidth() const override;

	/* Devuelve el alto de la viga */
	float getHeight() const override;
};


#endif
