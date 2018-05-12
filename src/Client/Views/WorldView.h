#ifndef __WORLDVIEW_H__
#define __WORLDVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include "Position.h"

class Player;

class WorldView{
	private:
		Gtk::Fixed world;
		Gtk::ScrolledWindow window;
		bool inactive_key_handler(GdkEventKey* key_event);
		bool inactive_button_handler(GdkEventButton *event);


	public:
		WorldView();
		~WorldView();

		void moveElement(Gtk::Widget& element, const Position& position);

		void removeElement(Gtk::Widget& element);

		void addElement(Gtk::Widget& element, const Position& position);

		Gtk::ScrolledWindow& getWindow();

		void enable_all_handlers(Player& player);
		void enable_movement_handlers(Player& player);
		void disable_handlers();
};


#endif
