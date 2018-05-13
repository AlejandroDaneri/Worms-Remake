#ifndef __CLIENTWEAPONBUTTON_H__
#define __CLIENTWEAPONBUTTON_H__

#include <gtkmm/togglebutton.h>
#include <gtkmm/image.h>

class WeaponButton {
	private:
		Gtk::ToggleButton button;
		Gtk::Image image;
		std::string weapon_name;

	public:
		WeaponButton(std::string& weapon_name);
		~WeaponButton();
		//WeaponButton(WeaponButton&& other);

		Gtk::Widget& getButton();
		
};


#endif
