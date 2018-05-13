#ifndef __CLIENTWEAPONBUTTON_H__
#define __CLIENTWEAPONBUTTON_H__

#include <gtkmm/togglebutton.h>
#include <gtkmm/image.h>
#include <string>

class Player;

class WeaponButton {
	private:
		std::string weapon_name;
		Player& player;
		Gtk::ToggleButton button;
		Gtk::Image image;

	public:
		WeaponButton(const std::string& weapon_name, Player& player);
		~WeaponButton();
		//WeaponButton(WeaponButton&& other);

		Gtk::Widget& getButton();
		
		void on_clicked_button();
};


#endif
