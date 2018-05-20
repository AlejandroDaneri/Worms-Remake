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
		Gtk::Button button;
		Gtk::Image image;

	public:
		WeaponButton(const std::string& weapon_name, unsigned int ammo, Player& player);
		~WeaponButton();
		//WeaponButton(WeaponButton&& other);

		Gtk::Widget& getButton();

		void setLabel(unsigned int ammo);
		
		void on_clicked_button();
		void on_released_button();
};


#endif
