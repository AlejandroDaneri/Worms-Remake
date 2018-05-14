#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include "WorldView.h"
#include "client_WeaponView.h"

//class WeaponView;
//class WorldView;

class ScreenView {
	private:
		Gtk::VBox screen;
		//WeaponView weapons_buttons;

	public:
		ScreenView(WorldView& world, WeaponView& weapons);
		~ScreenView();
		
		Gtk::VBox& getWindow();
};


#endif
