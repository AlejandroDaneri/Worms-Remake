#ifndef __WATER_H__
#define __WATER_H__

#include <gtkmm/image.h>
#include <gtkmm/layout.h>
#include <vector>

/* Clase que se encarga de controlar la vista del agua */
class Water{
	private:
		std::vector<Gtk::Image> images;
		
	public:
		/* Constructor */
		Water();

		/* Destructor */
		~Water();

		/* Muestra la imagen del agua */
		void show(Gtk::Layout& layout);
};

#endif
