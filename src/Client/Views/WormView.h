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
		bool dir_changed;
		std::string weapon;
		WormLifeView label;
		Gtk::Image image;
		Gtk::Grid worm;
		//std::queue<Glib::RefPtr<Gdk::Pixbuf>> queue;
		//Glib::RefPtr<Gdk::Pixbuf> full_image;

	public:
	    /* Constructor */
		WormView(WorldView& worldView, int life, char dir, Position pos, int player_id, const std::string& weapon);

		/* Destructor */
		~WormView();

		/* Constructor por movimiento */
		WormView(WormView&& other);


		/* Actualiza la posicion y vida del worm */
		void updateData(int new_life, char new_dir, const Position& new_pos, const std::string& weapon);

        /* Actualiza el arma del worm y cambia la imagen */
		void changeWeapon(const std::string &weapon);

		/* Devuelve la direccion del worm */
		char getDir() const;

		/* Elimina al worm del WorldView */
		void kill();

		/* Devuelve la vida del worm */
		int getLife() const;

		/* Devuelve el id del player que controla al worm */
		int getPlayerId() const;

		/* Devuelve el contenedor donde se encuentra la vista del worm */
		Gtk::Widget& getWidget() override;
};


#endif
