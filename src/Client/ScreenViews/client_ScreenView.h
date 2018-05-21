#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/grid.h>
#include "WorldView.h"
#include "client_WeaponView.h"


class ScreenView {
	private:
		Gtk::HBox screen;
		//Gtk::Grid screen2

	public:
		ScreenView(WorldView& world, WeaponView& weapons);
		~ScreenView();
		
		Gtk::Container& getWindow();
};


#endif
