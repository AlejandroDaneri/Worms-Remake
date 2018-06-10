#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>
#include "Viewable.h"
#include "WormLifeView.h"
#include "WalkingAnimation.h"
#include "WeaponAnimation.h"

#define DIR_RIGHT 1
#define DIR_LEFT -1

/* Clase que se encarga de controlar la vista de los worms */
class WormView : public Viewable {
private:
	int player_id;
	int life;
	bool is_moving;
	Position last_position;
	WormLifeView label;
	Gtk::Image image;
	Gtk::Grid worm;
	WalkingAnimation walkingAnimation;
	WeaponAnimation weaponAnimation;

	/* Actualiza la imagen del worm a la correspondiente segun las
	 * condiciones en las que se encuentra este */
	void
	setNewImage(char dir, bool colliding, bool is_current_worm, bool has_shot);

public:
	/* Constructor */
	WormView(WorldView& worldView, int life, char dir, Position pos,
			 int player_id);

	/* Destructor */
	~WormView();

	/* Constructor por movimiento */
	WormView(WormView&& other);


	/* Actualiza la posicion y vida del worm */
	void updateData(int new_life, char new_dir, const Position& new_pos,
					bool colliding, bool is_current_worm, bool has_shot);

	/* Actualiza la imagen del arma con el angulo actual */
	void updateScope(int angle);

	/* Actualiza el arma del worm y cambia la imagen */
	void changeWeapon(const std::string& weapon);

	/* Devuelve la direccion del worm */
	char getDir() const;

	/* Elimina la imagen del arma del worm */
	void removeWeaponImage();

	/* Devuelve la vida del worm */
	int getLife() const;

	/* Devuelve el id del player que controla al worm */
	int getPlayerId() const;

	/* Devuelve el contenedor donde se encuentra la vista del worm */
	Gtk::Widget& getWidget() override;

	/* Devuelve la imagen que contiene al worm */
	Gtk::Image& getImage();

	/* Cambia la imagen del worm por la animacion del worm
	 * festejando la victoria */
	void setVictory();

	/* Devuelve true si el gusano se esta moviendo */
	bool isMoving() const;

	/* Realiza la animacion del disparo del arma */
	void weaponShoot(const std::string& weapon);

	/* Resetea el focus del gusano */
	void resetFocus();
};


#endif
