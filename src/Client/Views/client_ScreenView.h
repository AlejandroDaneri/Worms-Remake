#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/fixed.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/scrolledwindow.h>
#include "Position.h"
#include "WorldView.h"
#include "client_WeaponView.h"

class Player;

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
