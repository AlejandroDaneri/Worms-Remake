#ifndef __WORLDVIEW_H__
#define __WORLDVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/fixed.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/scrolledwindow.h>
#include "Position.h"

class Player;

class WorldView{
	private:
		Gtk::Fixed world;
		Gtk::ScrolledWindow window;


	public:
		WorldView();
		~WorldView();

		void moveElement(Gtk::Widget& element, const Position& position, float width, float height);
		
		void moveScope(Gtk::Widget& scope, Gtk::Widget& worm, int angle);

		void removeElement(Gtk::Widget& element);

		void addElement(Gtk::Widget& element, const Position& position, float width, float height);

		Gtk::ScrolledWindow& getWindow();

};


#endif
