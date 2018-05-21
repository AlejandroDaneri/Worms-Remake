#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include "WorldView.h"
#include "client_WeaponView.h"
#include "TurnLabel.h"


class ScreenView {
	private:
		Gtk::VBox screen;
		Gtk::HBox world_box;

	public:
		ScreenView(WorldView& world, WeaponView& weapons, TurnLabel& label);
		~ScreenView();
		
		Gtk::Container& getWindow();
};


#endif
