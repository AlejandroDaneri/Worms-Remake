#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include "WorldView.h"
#include "client_WeaponView.h"
#include "TurnLabel.h"


class ScreenView {
	private:
		Gtk::HBox screen;
		Gtk::VBox world_label;

	public:
		ScreenView(WorldView& world, WeaponView& weapons, TurnLabel& label);
		~ScreenView();
		
		Gtk::Container& getWindow();
};


#endif
