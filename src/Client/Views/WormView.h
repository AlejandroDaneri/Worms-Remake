#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gdkmm/pixbuf.h>
#include "WormLifeView.h"
#include <queue>

#define DIR_RIGHT 1
#define DIR_LEFT -1


class WormView: public Viewable {
	private:
		int player_id;
		int life;
		char dir;
		std::string weapon;
		Position last_position;
		WormLifeView label;
		Gtk::Image image;
		Gtk::Grid worm;
		std::queue<Glib::RefPtr<Gdk::Pixbuf>> queue;
		Glib::RefPtr<Gdk::Pixbuf> full_image;

		void setNewImage(bool dir_changed, bool moved, bool colliding, bool is_current_worm);

		void setWeaponImage();

		void setMovementImage();

		void setStaticImage(bool dir_changed);

	public:
	    /* Constructor */
		WormView(WorldView& worldView, int life, char dir, Position pos, int player_id);

		/* Destructor */
		~WormView();

		/* Constructor por movimiento */
		WormView(WormView&& other);


		/* Actualiza la posicion y vida del worm */
		void updateData(int new_life, char new_dir, const Position& new_pos, bool colliding, bool is_current_worm);

        /* Actualiza el arma del worm y cambia la imagen */
		void changeWeapon(const std::string &weapon);

		/* Devuelve la direccion del worm */
		char getDir() const;

		/* Elimina al worm del WorldView */
		void kill();

		/* Elimina la imagen del arma del worm */
		void removeWeaponImage();

		/* Devuelve la vida del worm */
		int getLife() const;

		/* Devuelve el id del player que controla al worm */
		int getPlayerId() const;

		/* Devuelve el contenedor donde se encuentra la vista del worm */
		Gtk::Widget& getWidget() override;
};


#endif
