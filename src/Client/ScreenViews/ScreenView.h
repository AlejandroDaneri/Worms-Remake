#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include "WorldView.h"
#include "WeaponView.h"
#include "TurnLabel.h"
#include "PlayersList.h"


class ScreenView {
	private:
		Gtk::VBox screen;
		Gtk::HBox world_box;

        WorldView world;
        WeaponView weapons_view;

	public:
		ScreenView(Player& player, WeaponList& weapons,TurnLabel& label, PlayersList& players);
		~ScreenView();
		
		Gtk::Container& getWindow();

        WorldView& getWorld();
        WeaponView& getWeaponsView();
};


#endif
