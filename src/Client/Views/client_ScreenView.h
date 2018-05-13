#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include "WorldView.h"
#include "client_WeaponView.h"

//class WeaponView;
//class WorldView;

class ScreenView {
	private:
		Gtk::HBox screen;
		//WeaponView weapons_buttons;

	public:
		ScreenView(WorldView& world, WeaponView& weapons);
		~ScreenView();
		
		Gtk::HBox& getWindow();
};


#endif
