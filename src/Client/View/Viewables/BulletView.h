#ifndef __CLIENTBULLETVIEW_H__
#define __CLIENTBULLETVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>
#include "Viewable.h"

/* Clase que se encarga de controlar la vista de las balas */
class BulletView : public Viewable {
private:
	Gtk::Image image;
	std::string weapon_name;

public:
	/* Constructor */
	BulletView(WorldView& worldView, std::string weapon, Position pos);

	/* Destructor */
	~BulletView();

	/* Constructor por movimient */
	BulletView(BulletView&& other);

	/* Actualiza la posicion de la bala en la vista */
	void updateData(const Position& new_pos);

	/* Devuelve el contenedor de la bala */
	Gtk::Widget& getWidget() override;

	/* Devuelve el nombre del arma de la bala */
	std::string getName();
};


#endif
