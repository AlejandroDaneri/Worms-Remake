#ifndef __WINDVIEW_H__
#define __WINDVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

class WindView{
	private:
		Gtk::VBox container;
		Gtk::Label velocity;
		Gtk::Image direction;
		
		bool updateCallback(float wind);
		
	public:
		WindView();
		~WindView();
		
		//Actualiza la vista del viento
		void update(float wind);
		
		Gtk::VBox& getWindow();
};

#endif

