#ifndef __CLIENTWEAPONBUTTON_H__
#define __CLIENTWEAPONBUTTON_H__

#include <gtkmm/togglebutton.h>
#include <gtkmm/image.h>
#include <string>

class Player;

/* Clase que se encarga de mostrar el boton de un arma
 * junto con la informacion correspondiente a esa arma */
class WeaponButton {
	private:
		std::string weapon_name;
		Player& player;
		Gtk::Button button;
		Gtk::Image image;

	public:
		/* Constructor */
		WeaponButton(const std::string& weapon_name, unsigned int ammo, Player& player);

		/* Destructor */
		~WeaponButton();
		//WeaponButton(WeaponButton&& other);

		/* Devuelve el wiget del boton */
		Gtk::Widget& getButton();

		/* Setea el label del boton */
		void setLabel(unsigned int ammo);

		/* Handler del boton al ser clickeado */
		void onClickedButton();
};


#endif
