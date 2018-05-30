#ifndef __WATER_H__
#define __WATER_H__

#include <gtkmm/image.h>
#include <gtkmm/layout.h>
#include <vector>

class Water{
	private:
		std::vector<Gtk::Image> images;
		
	public:
		Water();
		
		~Water();
		
		void show(Gtk::Layout& layout);
};

#endif
