#ifndef __CLIENTWEAPONBUTTON_H__
#define __CLIENTWEAPONBUTTON_H__

#include <gtkmm/togglebutton.h>
#include <gtkmm/image.h>
#include <string>
#include "client_Player.h"

class WeaponButton {
	private:
		Gtk::ToggleButton button;
		Gtk::Image image;
		std::string weapon_name;
		Player& player;
		
		void on_clicked_button();

	public:
		WeaponButton(const std::string& weapon_name, Player& player);
		~WeaponButton();
		//WeaponButton(WeaponButton&& other);

		Gtk::Widget& getButton();
		
};


#endif
